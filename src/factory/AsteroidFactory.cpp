//
// Created by Maksym Maisak on 18/10/18.
//

#include "Factory.h"
#include "Rigidbody.h"
#include "Flicker.h"
#include "MyMath.h"
#include "Asteroid.h"
#include "DrawInfo.h"
#include "WrapAroundScreen.h"

const std::size_t NUM_VERTICES = 10;

std::shared_ptr<sf::Shape> makeAsteroidShape(const Asteroid::Config& config) {

    auto pShape = std::make_shared<sf::ConvexShape>(NUM_VERTICES);

    for (std::size_t i = 0; i < NUM_VERTICES; ++i) {

        sf::Vector2f point = en::polar2Cartesian(
            en::PI2 * (float)i / NUM_VERTICES,
            config.averageRadius + en::random(-config.radiusRange, config.radiusRange)
        );

        pShape->setPoint(i, point);
    }

    pShape->setFillColor(sf::Color::Transparent);
    pShape->setOutlineThickness(4.f);

    return pShape;
}

namespace game {

    en::Entity makeAsteroid(en::Engine& engine) {
        return makeAsteroid(engine, (Asteroid::Size)lround(en::random(0.f, 2.f)));
    }

    en::Entity makeAsteroid(en::Engine& engine, Asteroid::Size size) {

        sf::Vector2f position = engine.getWindow().getView().getSize();

        if (en::random() < 0.5f) {
            position.x = 0.f;
            position.y *= en::random();
        } else {
            position.x *= en::random();
            position.y = 0.f;
        }

        sf::Vector2f velocity = en::randomInCircle(400.f);

        return makeAsteroid(engine, size, position, velocity);
    }

    en::Entity makeAsteroid(
        en::Engine& engine,
        Asteroid::Size size,
        const sf::Vector2f& position,
        const sf::Vector2f& velocity
    ) {
        en::EntityRegistry& registry = engine.getRegistry();
        en::Entity e = registry.makeEntity();

        const Asteroid::Config& config = Asteroid::getConfig(size);
        std::shared_ptr<sf::Shape> shape = makeAsteroidShape(config);

        registry.add<Asteroid>(e, size);
        registry.add<en::DrawInfo>(e, shape);
        registry.add<Flicker>(e, shape);

        {
            auto& rb = registry.add<en::Rigidbody>(e);
            rb.velocity = velocity;
            rb.radius = config.averageRadius;
        }

        registry.add<en::Transformable>(e).setPosition(position);
        registry.add<WrapAroundScreen>(e);

        return e;
    }
}
