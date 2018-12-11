//
// Created by Maksym Maisak on 25/10/18.
//

#include "Factory.h"
#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "GameTime.h"
#include "Rigidbody.h"
#include "Bullet.h"
#include "DestroyTimer.h"
#include "DrawInfo.h"

static auto bulletShapePtr = []() {
    auto ptr = std::make_shared<sf::CircleShape>(10.f, 20);
    sf::Rect bounds = ptr->getLocalBounds();
    ptr->setOrigin(bounds.width * 0.5f, bounds.height * 0.5f);
    return ptr;
}();

namespace game {

    en::Entity makeBullet(en::Engine& engine, const sf::Vector2f& position, const sf::Vector2f& velocity) {

        en::EntityRegistry& registry = engine.getRegistry();
        en::Entity e = registry.makeEntity();

        registry.add<en::Transformable>(e).setPosition(position);
        {
            auto& rb = registry.add<en::Rigidbody>(e);
            rb.velocity = velocity;
            rb.invMass = 1.f / 0.01f;
        }

        registry.add<en::DrawInfo>(e, bulletShapePtr);
        registry.add<Bullet>(e);
        registry.add<en::DestroyTimer>(e, GameTime::now() + sf::seconds(2.f));

        return e;
    }
}