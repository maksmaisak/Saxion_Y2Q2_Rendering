//
// Created by Maksym Maisak on 27/9/18.
//
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Engine.h"
#include "Transformable.h"
#include "Actor.h"

#include <SFML/Graphics.hpp>

namespace en {

    const sf::Time TimestepFixed = sf::seconds(0.01f);
    const unsigned int FramerateCap = 240 ;

    Engine::Engine(unsigned int width, unsigned int height, bool enableVSync) {

        sf::ContextSettings contextSettings;
        contextSettings.antialiasingLevel = 8;
        m_window.create(sf::VideoMode(width, height), "Game", sf::Style::Default, contextSettings);
        m_window.setVerticalSyncEnabled(enableVSync);
    }

    void Engine::run() {

        sf::Clock fixedUpdateClock;
        sf::Time fixedUpdateLag = sf::Time::Zero;

        sf::Clock drawClock;
        sf::Time timeSinceLastDraw = sf::Time::Zero;

        const float timestepFixedSeconds = TimestepFixed.asSeconds();
        const sf::Time timestepDraw = sf::seconds(1.f / FramerateCap);

        while (m_window.isOpen()) {

            sf::Event event{};
            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) m_window.close();
            }

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
        }
    }

    void Engine::update(float dt) {

        for (auto& pSystem : m_systems) pSystem->update(dt);
        m_scheduler.update(dt);
    }

    void Engine::draw() {

        m_window.clear();

        for (auto& pSystem : m_systems) pSystem->draw();

        m_window.display();
    }

    void Engine::setParent(Entity child, std::optional<Entity> newParent) {

        auto& childTransformable = m_registry.get<en::Transformable>(child);

        std::optional<en::Entity> oldParent = childTransformable.m_parent;

        if (oldParent.has_value()) {

            if (*oldParent == newParent) return;
            m_registry.get<en::Transformable>(*oldParent).removeChild(child);
        }

        if (newParent.has_value()) {

            auto& parentTransformable = m_registry.get<en::Transformable>(*newParent);
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
