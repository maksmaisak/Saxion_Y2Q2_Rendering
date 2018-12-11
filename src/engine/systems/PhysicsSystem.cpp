//
// Created by Maksym Maisak on 20/10/18.
//

#include <SFML/Graphics.hpp>
#include "PhysicsSystem.h"
#include "Transformable.h"
#include "Rigidbody.h"
#include "PhysicsUtils.h"
#include "Messaging.h"
#include "Collision.h"

namespace en {

    void PhysicsSystem::update(float dt) {

        auto view = m_registry->with<en::Rigidbody, en::Transformable>();
        for (en::Entity entity : view) {

            auto& rb = m_registry->get<en::Rigidbody>(entity);
            auto& tf = m_registry->get<en::Transformable>(entity);

            sf::Vector2f movement = rb.velocity * dt;

            bool didCollide = false;
            for (en::Entity other : view) {

                if (entity == other) continue;

                auto& otherRb = m_registry->get<en::Rigidbody>(other);
                auto& otherTf = m_registry->get<en::Transformable>(other);

                std::optional<en::Hit> hit = en::circleVsCircleContinuous(
                    tf.getPosition(), rb.radius, movement,
                    otherTf.getPosition(), otherRb.radius
                );

                if (hit.has_value()) {

                    en::resolve(
                        rb.velocity, rb.invMass,
                        otherRb.velocity, otherRb.invMass,
                        hit->normal, std::min(rb.bounciness, otherRb.bounciness)
                    );
                    tf.move(movement * hit->timeOfImpact);
                    didCollide = true;

                    en::Receiver<en::Collision>::accept({*hit, entity, other});

                    break;
                }
            }

            if (!didCollide) {
                tf.move(movement);
            }
        }
    }
}
