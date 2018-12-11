//
// Created by Maksym Maisak on 24/10/18.
//

#include "Rigidbody.h"
#include "PlayerControlsSystem.h"
#include "Entity.h"
#include "Player.h"
#include "Destroy.h"
#include "Engine.h"
#include "MyMath.h"
#include "Input.h"

inline bool accelerateButtonPressed() {

    return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}

inline void rotate(en::Transformable& tf, float rotationSpeed, float dt) {

    float currentRotation = tf.getRotation();
    float input = en::getAxisHorizontal();
    if (!en::isZero(input)) {
        currentRotation += input * rotationSpeed * dt;
        tf.setRotation(currentRotation);
    }
}

inline void accelerate(en::Rigidbody& rb, en::Transformable& tf, float acceleration, float dt) {
    rb.velocity += en::getForward(tf.getGlobalTransform()) * acceleration * dt;
}

inline void drag(en::Rigidbody& rb, float drag, float dt) {

    if (en::isZero(rb.velocity)) return;
    rb.velocity -= en::normalized(rb.velocity) * std::min(drag * dt, en::magnitude(rb.velocity));
}

void PlayerControlsSystem::update(float dt) {

    bool enginesOn = accelerateButtonPressed();

    for (Entity e : m_registry->with<Player, en::Transformable, en::Rigidbody>()) {

        auto& player = m_registry->get<Player>(e);
        auto& tf = m_registry->get<en::Transformable>(e);
        auto& rb = m_registry->get<en::Rigidbody>(e);

        rotate(tf, player.rotationSpeed, dt);

        if (enginesOn) accelerate(rb, tf, player.acceleration, dt);
        else drag(rb, player.drag, dt);

        en::truncate(rb.velocity, player.maxSpeed);

        if (player.exhaustParticleSystem) {
            player.exhaustParticleSystem->setIsEmissionActive(enginesOn && !m_registry->tryGet<Destroy>(e));
        }
    }

    System::update(dt);
}
