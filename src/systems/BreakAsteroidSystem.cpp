//
// Created by Maksym Maisak on 24/10/18.
//

#include "BreakAsteroidSystem.h"
#include <iostream>
#include <optional>
#include <tuple>
#include <components/Rigidbody.h>
#include "Asteroid.h"
#include "Bullet.h"
#include "Factory.h"
#include "Destroy.h"

void split(en::Engine& engine, en::EntityRegistry& registry, en::Entity asteroidEntity, const Asteroid& asteroid) {

    assert(asteroid.size > Asteroid::Size::Small);
    const auto piecesSize = (Asteroid::Size)((std::size_t)asteroid.size - 1);
    const Asteroid::Config& piecesConfig = Asteroid::getConfig(piecesSize);

    const auto& transform = registry.get<en::Transformable>(asteroidEntity).getGlobalTransform();
    sf::Vector2f position = en::getPosition(transform);
    sf::Vector2f velocity = registry.get<en::Rigidbody>(asteroidEntity).velocity;

    const std::size_t NUM_PIECES = 2;
    const float radius = piecesConfig.averageRadius + piecesConfig.radiusRange;
    const float startAngle = en::random(0.f, en::PI2);
    for (std::size_t i = 0; i < NUM_PIECES; ++i) {

        const float angle = startAngle + en::PI2 * (float)i / NUM_PIECES;
        const sf::Vector2f offset = en::polar2Cartesian(angle, radius);

        const sf::Vector2f relativeVelocity = en::normalized(offset) * 100.f;

        game::makeAsteroid(engine, piecesSize, position + offset, velocity + relativeVelocity);
    }
}

void BreakAsteroidSystem::receive(const en::Collision& collision) {

    auto [success, asteroidEntity, bulletEntity] = en::getCollision<Asteroid, Bullet>(*m_registry, collision);
    if (!success) return;

    m_registry->add<en::Destroy>(asteroidEntity);
    m_registry->add<en::Destroy>(bulletEntity);

    auto& asteroid = m_registry->get<Asteroid>(asteroidEntity);
    if (asteroid.size > Asteroid::Size::Small) {
        split(*m_engine, *m_registry, asteroidEntity, asteroid);
    }
}
