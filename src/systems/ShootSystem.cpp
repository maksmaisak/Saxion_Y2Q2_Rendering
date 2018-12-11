//
// Created by Maksym Maisak on 25/10/18.
//

#include "ShootSystem.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include "EntityRegistry.h"
#include "Input.h"
#include "MyMath.h"
#include "GameTime.h"
#include "DestroyTimer.h"

#include "Transformable.h"
#include "Rigidbody.h"
#include "Player.h"
#include "Bullet.h"
#include "Factory.h"

void ShootSystem::update(float dt) {

    bool shouldFire = sf::Keyboard::isKeyPressed(sf::Keyboard::F);
    if (!shouldFire) return;

    sf::Time now = GameTime::now();

    for (Entity e : m_registry->with<Player, en::Transformable>()) {

        auto& player = m_registry->get<Player>(e);
        if (player.timeWhenCanShootAgain > now) continue;

        player.timeWhenCanShootAgain = now + player.shootInterval;

        auto& tf = m_registry->get<en::Transformable>(e);
        const sf::Transform& playerTransform = tf.getGlobalTransform();

        sf::Vector2f forward  = en::getForward(playerTransform);
        sf::Vector2f position = playerTransform.transformPoint(0, 0) + forward * 50.f;

        game::makeBullet(*m_engine, position, forward * 4000.f);
    }
}
