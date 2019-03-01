//
// Created by Maksym Maisak on 27/9/18.
//
#include <iostream>
#include <cmath>
#include <algorithm>
#include <Gl/glew.h>
#include <SFML/Graphics.hpp>
#include <type_traits>

#include "Engine.h"
#include "Actor.h"
#include "ComponentsToLua.h"
#include "GLHelpers.h"
#include "GameTime.h"
#include "Transform.h"
#include "Name.h"
#include "LuaScene.h"
#include "LuaState.h"
#include "MetatableHelper.h"
#include "ClosureHelper.h"
#include "Resources.h"
#include "Material.h"
#include "KeyboardHelper.h"
#include "MouseHelper.h"
#include "Sound.h"

using namespace en;

const sf::Time TimestepFixed = sf::seconds(0.01f);

Engine::Engine() :
    m_sceneManager(this),
    m_lua(std::make_unique<LuaState>()) {}

void Engine::initialize() {

    initializeLua();
    initializeWindow(m_window);
    printGLContextVersionInfo();
    initializeGlew();
}

void Engine::run() {

    sf::Clock fixedUpdateClock;
    sf::Time fixedUpdateLag = sf::Time::Zero;

    const float timestepFixedSeconds = TimestepFixed.asSeconds();
    const sf::Time timestepDraw = sf::microseconds((sf::Int64)(1000000.0 / m_framerateCap));

    sf::Clock drawClock;

    while (m_window.isOpen()) {

        fixedUpdateLag += fixedUpdateClock.restart();
        while (fixedUpdateLag >= TimestepFixed) {
            update(timestepFixedSeconds);
            fixedUpdateLag -= TimestepFixed;
        }

        if (drawClock.getElapsedTime() >= timestepDraw) {

            m_fps = (float)(1000000.0 / drawClock.restart().asMicroseconds());
            auto frameClock = sf::Clock();
            draw();
            m_frameTimeMicroseconds = frameClock.getElapsedTime().asMicroseconds();

        } else {
            do sf::sleep(sf::microseconds(1));
            while (drawClock.getElapsedTime() < timestepDraw && fixedUpdateLag + fixedUpdateClock.getElapsedTime() < TimestepFixed);
        }

        processWindowEvents();
    }
}

void Engine::update(float dt) {

    auto* currentScene = m_sceneManager.getCurrentScene();
    if (currentScene) currentScene->update(dt);

    for (auto& pSystem : m_systems)
        pSystem->update(dt);

    m_scheduler.update(dt);

    utils::KeyboardHelper::update();
    utils::MouseHelper::update();
}

void Engine::draw() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (auto& pSystem : m_systems)
        pSystem->draw();

    m_window.display();
}

void Engine::initializeWindow(sf::RenderWindow& window) {

    std::cout << "Initializing window..." << std::endl;

    auto& lua = getLuaState();
    lua_getglobal(lua, "Config");
    auto popConfig = lua::PopperOnDestruct(lua);
    unsigned int width      = lua.tryGetField<unsigned int>("width").value_or(800);
    unsigned int height     = lua.tryGetField<unsigned int>("height").value_or(600);
    bool vsync              = lua.tryGetField<bool>("vsync").value_or(true);
    bool fullscreen         = lua.tryGetField<bool>("fullscreen").value_or(false);
    std::string windowTitle = lua.tryGetField<std::string>("windowTitle").value_or("Game");

    auto contextSettings = sf::ContextSettings(24, 8, 8, 4, 5, sf::ContextSettings::Attribute::Core | sf::ContextSettings::Attribute::Debug);
    window.create(sf::VideoMode(width, height), windowTitle, fullscreen ? sf::Style::Fullscreen : sf::Style::Default, contextSettings);
    window.setVerticalSyncEnabled(vsync);
    window.setFramerateLimit(0);
    window.setActive(true);

    std::cout << "Window initialized." << std::endl << std::endl;
}

void Engine::printGLContextVersionInfo() {

    std::cout << "Context info:" << std::endl;
    std::cout << "----------------------------------" << std::endl;
    //print some debug stats for whoever cares
    const GLubyte* vendor      = glGetString(GL_VENDOR);
    const GLubyte* renderer    = glGetString(GL_RENDERER);
    const GLubyte* version     = glGetString(GL_VERSION);
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    //nice consistency here in the way OpenGl retrieves values
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    printf("GL Vendor : %s\n", vendor);
    printf("GL Renderer : %s\n", renderer);
    printf("GL Version (string) : %s\n", version);
    printf("GL Version (integer) : %d.%d\n", major, minor);
    printf("GLSL Version : %s\n", glslVersion);

    std::cout << "----------------------------------" << std::endl << std::endl;
}

void Engine::initializeGlew() {

    std::cout << "Initializing GLEW..." << std::endl;

    GLint glewStatus = glewInit();
    if (glewStatus == GLEW_OK) {
        std::cout << "Initialized GLEW: OK" << std::endl;
    } else {
        std::cerr << "Initialized GLEW: FAILED" << std::endl;
    }
}

std::string testFreeFunction() {

    std::cout << "Free function called from lua" << std::endl;
    return "Result returned from free function";
}

int makeActors(lua_State* L) {

    luaL_checktype(L, 1, LUA_TTABLE);
    Engine& engine = *lua::check<Engine*>(L, lua_upvalueindex(1));
    ComponentsToLua::makeEntities(L, engine, 1);

    return 0;
}

int makeActorFromLua(lua_State* L) {

    Engine& engine = *lua::check<Engine*>(L, lua_upvalueindex(1));

    // makeActor(table)
    if (lua_istable(L, 1)) {

        Actor actor = ComponentsToLua::makeEntity(L, engine, 1);
        ComponentsToLua::addComponents(L, actor, 1);
        lua::push(L, actor);

        return 1;
    }

    // makeActor(name, [table])
    Actor actor = engine.makeActor(luaL_checkstring(L, 1));
    if (lua_istable(L, 2))
        ComponentsToLua::addComponents(L, actor, 2);
    lua::push(L, actor);
    return 1;
}

int makeMaterial(lua_State* L) {

    auto lua = LuaState(L);

    std::shared_ptr<Material> material;
    if (lua.is<std::string>(1)) {

        if (lua_isnoneornil(L, 2)) {
            material = Resources<Material>::get(lua.to<std::string>(1));
        } else {
            lua_pushvalue(L, 2);
            material = Resources<Material>::get(lua.to<std::string>(1), lua);
        }
    } else {

        if (lua_isnoneornil(L, 1)) {
            material = std::make_shared<Material>("lit");
        } else {
            material = std::make_shared<Material>(lua);
        }
    }

    lua.push(std::move(material));
    return 1;
}

int loadScene(lua_State* L) {

    Engine* engine = lua::check<Engine*>(L, lua_upvalueindex(1));

    if (lua::is<std::string>(L, 1)) {

        std::string path = lua::to<std::string>(L, 1);
        engine->getScheduler().delay(sf::microseconds(0), [=](){
            engine->getSceneManager().setCurrentScene<LuaScene>(engine->getLuaState(), path);
        });

    } else if (lua_istable(L, 1)) {

        lua_pushvalue(L, 1);
        // Have to make a shared_ptr because LuaReference is non-copyable.
        // Capturing a non-copyable type would make the lambda non-copyable,
        // which would make it impossible to make a std::function out of it.
        auto ref = std::make_shared<LuaReference>(L);
        engine->getScheduler().delay(sf::microseconds(0), [engine, ref](){
            engine->getSceneManager().setCurrentScene<LuaScene>(std::move(*ref));
        });
    }

    return 0;
}

template<>
struct ResourceLoader<sf::SoundBuffer> {

    inline static std::shared_ptr<sf::SoundBuffer> load(const std::string& filepath) {

        auto buffer = std::make_shared<sf::SoundBuffer>();
        if (!buffer->loadFromFile(filepath)) {
            std::cerr << "Couldn't load sound from: " << filepath << std::endl;
            return nullptr;
        }

        return buffer;
    }
};

void Engine::initializeLua() {

    LUA_REGISTER_TYPE(Actor);

    auto& lua = getLuaState();

    lua_newtable(lua);
    {
        lua.setField("testValue", 3.1415926f);
        lua.setField("testFreeFunction", &testFreeFunction);
        lua.setField("testMemberFunction", &Engine::testMemberFunction, this);
        lua.setField("find", [this](const std::string& name) -> std::optional<Actor> {
            Actor actor = findByName(name);
            if (actor)
                return std::make_optional(actor);
            return std::nullopt;
        });

        lua.push(this);
        lua_pushcclosure(lua, &makeActors, 1);
        lua_setfield(lua, -2, "makeActors");

        lua.push(this);
        lua_pushcclosure(lua, &makeActorFromLua, 1);
        lua_setfield(lua, -2, "makeActor");

        lua.setField("getTime", [](){return GameTime::now().asSeconds();});

        lua.push(this);
        lua_pushcclosure(lua, &loadScene, 1);
        lua_setfield(lua, -2, "loadScene");

        lua.setField("quit", [this](){m_shouldExit = true;});

        // TODO make addProperty work on both tables and their metatables
        //lua::addProperty(lua, "time", lua::Property<float>([](){return GameTime::now().asSeconds();}));

        lua.setField("makeMaterial", &makeMaterial);

        lua.setField("makeSound", [](const std::string& filepath) {
            return std::make_shared<Sound>(config::ASSETS_PATH + filepath);
        });

        lua.setField("getSound", [](const std::string& filepath) {
            return Resources<Sound>::get(config::ASSETS_PATH + filepath);
        });

        // Game.keyboard
        lua_pushvalue(lua, -1);
        lua_newtable(lua);
        {
            lua.setField("isHeld", &utils::KeyboardHelper::isHeld);
            lua.setField("isDown", &utils::KeyboardHelper::isDown);
            lua.setField("isUp"  , &utils::KeyboardHelper::isUp);
        }
        lua_setfield(lua, -2, "keyboard");

        // Game.mouse
        lua_pushvalue(lua, -1);
        lua_newtable(lua);
        {
            lua.setField("isHeld", [](int buttonNum){return utils::MouseHelper::isHeld((sf::Mouse::Button)(buttonNum - 1));});
            lua.setField("isDown", [](int buttonNum){return utils::MouseHelper::isDown((sf::Mouse::Button)(buttonNum - 1));});
            lua.setField("isUp"  , [](int buttonNum){return utils::MouseHelper::isUp  ((sf::Mouse::Button)(buttonNum - 1));});
        }
        lua_setfield(lua, -2, "mouse");
    }
    lua_setglobal(lua, "Game");

    ComponentsToLua::printDebugInfo();

    if (lua.doFileInNewEnvironment(config::SCRIPT_PATH + "config.lua")) {
        lua_setglobal(lua, "Config");
    }

    lua_getglobal(lua, "Config");
    m_framerateCap = lua.tryGetField<unsigned int>("framerateCap").value_or(m_framerateCap);
    lua.pop();
}

void Engine::testMemberFunction() {

    std::cout << "Member function called from lua" << std::endl;
}

void Engine::processWindowEvents() {

    sf::Event event{};
    while (m_window.pollEvent(event)) {

        switch (event.type) {

            case sf::Event::Closed:
                m_shouldExit = true;
                break;

            case sf::Event::Resized:
                // TODO move this to the render system
                // Unconstrained match viewport scaling
                glViewport(0, 0, event.size.width, event.size.height);
                break;

            default:
                break;
        }

        Receiver<sf::Event>::broadcast(event);
    }

    if (m_shouldExit) {
        m_window.close();
    }
}

Actor Engine::actor(Entity entity) const {
    return Actor(*const_cast<Engine*>(this), entity);
}

Actor Engine::makeActor() {
    return actor(m_registry.makeEntity());
}

Actor Engine::makeActor(const std::string& name) {
    return actor(m_registry.makeEntity(name));
}

Actor Engine::findByName(const std::string& name) const {
    return actor(m_registry.findByName(name));
}

Engine::~Engine() {

    // If sf::SoundBuffer is being destroyed when statics are destroyed when the app quits,
    // that causes OpenAL to throw an error. This prevents that.
    Resources<Sound>::removeUnused();
    Resources<sf::SoundBuffer>::removeUnused();
}
