//
// Created by Maksym Maisak on 27/9/18.
//
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Engine.h"
#include "Actor.h"
#include <Gl/glew.h>
#include <SFML/Graphics.hpp>

namespace en {

    const sf::Time TimestepFixed = sf::seconds(0.01f);
    const unsigned int FramerateCap = 240;

    Engine::Engine() : m_sceneManager(this) {}

    void Engine::initialize() {

        initializeWindow(m_window);
        printGLContextVersionInfo();
        initializeGlew();
    }

    void Engine::initializeWindow(sf::RenderWindow& window) {

        std::cout << "Initializing window..." << std::endl;

        m_lua.doFileInNewEnvironment("assets/scripts/config.lua");
        unsigned int width  = m_lua.getField<unsigned int>("width" ).value_or(800);
        unsigned int height = m_lua.getField<unsigned int>("height").value_or(600);
        lua_pop(m_lua, 1);

        auto contextSettings = sf::ContextSettings(24, 8, 8, 3, 3);
        window.create(sf::VideoMode(width, height), "Game", sf::Style::Default, contextSettings);
        window.setVerticalSyncEnabled(true);
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

        for (auto& pSystem : m_systems) pSystem->update(dt);
        m_scheduler.update(dt);
    }

    void Engine::draw() {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_window.clear();
        for (auto& pSystem : m_systems) pSystem->draw();
        m_window.display();
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

    void Engine::setParent(Entity child, std::optional<Entity> newParent) {

        auto& childTransformable = m_registry.get<en::TransformableSFML>(child);

        std::optional<en::Entity> oldParent = childTransformable.m_parent;

        if (oldParent.has_value()) {

            if (*oldParent == newParent) return;
            m_registry.get<en::TransformableSFML>(*oldParent).removeChild(child);
        }

        if (newParent.has_value()) {

            auto& parentTransformable = m_registry.get<en::TransformableSFML>(*newParent);
            parentTransformable.addChild(child);
        }

        childTransformable.m_parent = newParent;
        childTransformable.m_globalTransformNeedUpdate = true;
    }

    Actor Engine::actor(Entity entity) {
        return Actor(*this, entity);
    }

    Actor Engine::makeActor() {
        return Actor(*this, m_registry.makeEntity());
    }
}
