//
// Created by Maksym Maisak on 20/10/18.
//

#include <SFML/Graphics.hpp>
#include "PhysicsSystem.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "PhysicsUtils.h"
#include "Messaging.h"
#include "Collision.h"

namespace en {

    PhysicsSystem& PhysicsSystem::setGravity(const glm::vec3& gravity) {

        m_gravity = gravity;
        return *this;
    }

    void PhysicsSystem::update(float dt) {

        glm::vec3 gravityDeltaV = m_gravity * dt;

        auto view = m_registry->with<en::Rigidbody, en::Transform>();
        for (en::Entity entity : view) {

            auto& rb = m_registry->get<en::Rigidbody>(entity);
            if (rb.isKinematic) continue;

            auto& tf = m_registry->get<en::Transform>(entity);

            rb.velocity += gravityDeltaV;
            glm::vec3 movement = rb.velocity * dt;

            bool didCollide = false;
            for (en::Entity other : view) {

                if (entity == other) continue;

                auto& otherRb = m_registry->get<en::Rigidbody>(other);
                auto& otherTf = m_registry->get<en::Transform>(other);

                std::optional<en::Hit> hit = en::circleVsCircleContinuous(
                         tf.getWorldPosition(),      rb.radius, movement,
                    otherTf.getWorldPosition(), otherRb.radius
                );

                if (hit.has_value()) {

                    en::resolve(
                             rb.velocity,      rb.invMass,
                        otherRb.velocity, otherRb.invMass,
                        hit->normal, std::min(rb.bounciness, otherRb.bounciness)
                    );
                    tf.move(movement * hit->timeOfImpact);
                    didCollide = true;

                    en::Receiver<en::Collision>::broadcast({*hit, entity, other});
                    break;
                }
            }

            if (!didCollide) {
                tf.move(movement);
            }
        }
    }
}
