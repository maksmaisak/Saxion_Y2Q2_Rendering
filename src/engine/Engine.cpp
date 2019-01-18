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

#include "MetatableHelper.h"
#include "Transform.h"
#include "Name.h"

namespace en {

    const sf::Time TimestepFixed = sf::seconds(0.01f);
    const unsigned int FramerateCap = 240;

    Engine::Engine() : m_sceneManager(this) {}

    void Engine::initialize() {

        initializeWindow(m_window);
        printGLContextVersionInfo();
        initializeGlew();
        initializeLua();
    }

    void Engine::run() {

        sf::Clock fixedUpdateClock;
        sf::Time fixedUpdateLag = sf::Time::Zero;

        sf::Clock drawClock;
        sf::Time timeSinceLastDraw = sf::Time::Zero;

        const float timestepFixedSeconds = TimestepFixed.asSeconds();
        const sf::Time timestepDraw = sf::seconds(1.f / FramerateCap);

        while (m_window.isOpen()) {

            fixedUpdateLag += fixedUpdateClock.restart();
            while (fixedUpdateLag >= TimestepFixed) {
                update(timestepFixedSeconds);
                fixedUpdateLag -= TimestepFixed;
            }

            if (drawClock.getElapsedTime() >= timestepDraw) {
                m_fps = 1.f / drawClock.getElapsedTime().asSeconds();
                draw();
                drawClock.restart();
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

        for (auto& pSystem : m_systems) pSystem->update(dt);

        m_scheduler.update(dt);
    }

    void Engine::draw() {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (auto& pSystem : m_systems) pSystem->draw();
        m_window.display();
    }

    void Engine::initializeWindow(sf::RenderWindow& window) {

        std::cout << "Initializing window..." << std::endl;

        m_lua.doFileInNewEnvironment("assets/scripts/config.lua");
        unsigned int width  = m_lua.getField<unsigned int>("width" ).value_or(800);
        unsigned int height = m_lua.getField<unsigned int>("height").value_or(600);
        bool useVSync = m_lua.getField<bool>("vSync").value_or(true);
        lua_pop(m_lua, 1);

        auto contextSettings = sf::ContextSettings(24, 8, 8, 3, 3);
        window.create(sf::VideoMode(width, height), "Game", sf::Style::Default, contextSettings);
        window.setVerticalSyncEnabled(useVSync);
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

    void Engine::initializeLua() {

        LUA_REGISTER_TYPE(Actor);

        // Configure metatables of all registered component types
        ComponentsToLua::populateMetatables(m_lua);

        {
            lua_newtable(m_lua);

            m_lua.setField("testValue", 3.1415926f);
            m_lua.setField("testFreeFunction", &testFreeFunction);
            m_lua.setField("testMemberFunction", &Engine::testMemberFunction, this);
            m_lua.setField("findByName", [this](const std::string& name) -> std::optional<Actor> {
                Actor actor = findByName(name);
                if (actor) return std::make_optional(actor);
                return std::nullopt;
            });
            m_lua.setField("makeActor", [this](const std::string& name) { return makeActor(name); });

            lua_setglobal(m_lua, "Game");
        }

        ComponentsToLua::printDebugInfo();
    }

    void Engine::testMemberFunction() {

        std::cout << "Member function called from lua" << std::endl;
    }

    void Engine::processWindowEvents() {

        bool shouldExit = false;

        sf::Event event{};
        while (m_window.pollEvent(event)) {

            switch (event.type) {

                case sf::Event::Closed:
                    shouldExit = true;
                    break;

                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) shouldExit = true;
                    break;

                case sf::Event::Resized:
                    //would be better to move this to the render system
                    //this version implements unconstrained match viewport scaling
                    glViewport(0, 0, event.size.width, event.size.height);
                    break;

                default:
                    break;
            }

            Receiver<sf::Event>::broadcast(event);
        }

        if (shouldExit) {
            m_window.close();
        }
    }

    Actor Engine::actor(Entity entity) {
        return Actor(*this, entity);
    }

    Actor Engine::makeActor() {
        return actor(m_registry.makeEntity());
    }

    Actor Engine::makeActor(const std::string& name) {
        return actor(m_registry.makeEntity(name));
    }

    Actor Engine::findByName(const std::string& name) {
        return actor(m_registry.findByName(name));
    }
}
