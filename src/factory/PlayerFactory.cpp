//
// Created by Maksym Maisak on 18/10/18.
//

#include "Factory.h"
#include "Actor.h"
#include "DrawInfo.h"
#include "Rigidbody.h"
#include "ParticleSystem.h"
#include "Transformable.h"
#include "Player.h"
#include "Flicker.h"
#include "WrapAroundScreen.h"

std::shared_ptr<sf::Shape> makePlayerShape() {

    auto pShape = std::make_shared<sf::ConvexShape>(4);

    pShape->setPoint(0, { 70,  0 });
    pShape->setPoint(1, {-70,  50});
    pShape->setPoint(2, {-50,  0 });
    pShape->setPoint(3, {-70, -50});

    pShape->setScale(0.5f, 0.5f);
    pShape->setRotation(-90.f);

    pShape->setFillColor(sf::Color::Black);
    pShape->setOutlineThickness(4.f);

    return pShape;
}

void addTransformable(Engine& engine, Entity player) {

    sf::Vector2f size = engine.getWindow().getView().getSize();
    auto& tf = engine.getRegistry().add<en::Transformable>(player);
    tf.setPosition(size.x / 2.f, size.y * 3.f / 4.f);
    tf.setScale(0.75f, 0.75f);
}

Entity addExhaust(Engine& engine, Entity player) {

    EntityRegistry& registry = engine.getRegistry();

    Actor exhaust = engine.makeActor();
    auto& tf = registry.add<en::Transformable>(exhaust);
    tf.move(0, 30.f);
    engine.setParent(exhaust, player);

    auto& exhaustParticleSystem = exhaust.add<ParticleSystem>(10000u);
    {
        auto pParticleDrawable = std::make_shared<sf::CircleShape>(4.f, 3);
        pParticleDrawable->setOrigin(0.5f, 0.5f);
        exhaustParticleSystem.setDrawable(pParticleDrawable);

        auto s = exhaustParticleSystem.getSettings();
        s.emissionInterval = sf::microseconds(400);
        s.emissionRadius = 10.f;
        s.startVelocity = {0, 1000.f};
        s.startVelocityRandomness = 100.f;
        s.particleLifetime = sf::seconds(0.5f);
        exhaustParticleSystem.setSettings(s);
    }

    registry.get<Player>(player).exhaustParticleSystem = &exhaustParticleSystem;

    return exhaust;
}

namespace game {

    Entity makePlayer(Engine& engine) {

        EntityRegistry& registry = engine.getRegistry();
        Entity e = registry.makeEntity();

        addTransformable(engine, e);

        std::shared_ptr<sf::Shape> shape = makePlayerShape();
        registry.add<en::DrawInfo>(e, shape);
        registry.add<Flicker>(e, shape);
        registry.add<Player>(e);
        registry.add<WrapAroundScreen>(e);

        {
            auto& rb = registry.add<en::Rigidbody>(e);
            rb.radius = 20.f;
            rb.invMass = 1.f / 0.5f;
        }

        addExhaust(engine, e);

        return e;
    }
}

