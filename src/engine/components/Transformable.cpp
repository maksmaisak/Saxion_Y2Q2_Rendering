//
// Created by Maksym Maisak on 22/10/18.
//

#include "Transformable.h"

#include <cmath>
#include <algorithm>
#include "EntityRegistry.h"

using sf::Vector2f;
using sf::Transform;

namespace en {

    Transformable::Transformable() :
        m_origin(0, 0),
        m_position(0, 0),
        m_rotation(0),
        m_scale(1, 1),

        m_transform(),
        m_localTransformNeedUpdate(true),

        m_inverseTransform(),
        m_localInverseTransformNeedUpdate(true),

        m_globalTransform(),
        m_globalTransformNeedUpdate(true)
        {}

    void Transformable::setPosition(float x, float y) {

        m_position.x = x;
        m_position.y = y;
        localTransformChanged();
    }

    void Transformable::setPosition(const Vector2f& position) {
        setPosition(position.x, position.y);
    }

    void Transformable::setRotation(float angle) {

        m_rotation = static_cast<float>(fmod(angle, 360));
        if (m_rotation < 0)
            m_rotation += 360.f;

        localTransformChanged();
    }

    void Transformable::setScale(float factorX, float factorY) {

        m_scale.x = factorX;
        m_scale.y = factorY;
        localTransformChanged();
    }

    void Transformable::setScale(const Vector2f& factors) {
        setScale(factors.x, factors.y);
    }

    void Transformable::setOrigin(float x, float y) {

        m_origin.x = x;
        m_origin.y = y;
        localTransformChanged();
    }

    void Transformable::setOrigin(const Vector2f& origin) { setOrigin(origin.x, origin.y); }

    const Vector2f& Transformable::getPosition() const { return m_position; }
    float Transformable::getRotation()           const { return m_rotation; }
    const Vector2f& Transformable::getScale()    const { return m_scale;    }
    const Vector2f& Transformable::getOrigin()   const { return m_origin;   }

    void Transformable::move(float offsetX, float offsetY) { setPosition(m_position.x + offsetX, m_position.y + offsetY); }

    void Transformable::move(const Vector2f& offset) { setPosition(m_position.x + offset.x, m_position.y + offset.y); }

    void Transformable::rotate(float angle) { setRotation(m_rotation + angle); }

    void Transformable::scale(float factorX, float factorY) { setScale(m_scale.x * factorX, m_scale.y * factorY); }

    void Transformable::scale(const Vector2f& factor) { setScale(m_scale.x * factor.x, m_scale.y * factor.y); }

    const Transform& Transformable::getLocalTransform() const {

        // Recompute the combined transform if needed
        if (m_localTransformNeedUpdate) {

            float angle = -m_rotation * 3.141592654f / 180.f;

            float cosine = static_cast<float>(std::cos(angle));
            float sine   = static_cast<float>(std::sin(angle));

            float sxc = m_scale.x * cosine;
            float syc = m_scale.y * cosine;
            float sxs = m_scale.x * sine;
            float sys = m_scale.y * sine;

            float tx = -m_origin.x * sxc - m_origin.y * sys + m_position.x;
            float ty =  m_origin.x * sxs - m_origin.y * syc + m_position.y;

            m_transform = Transform(
                sxc , sys, tx,
                -sxs, syc, ty,
                0.f , 0.f, 1.f
            );
            m_localTransformNeedUpdate = false;
        }

        return m_transform;
    }

    const Transform& Transformable::getInverseLocalTransform() const {

        // Recompute the inverse transform if needed
        if (m_localInverseTransformNeedUpdate) {
            m_inverseTransform = getLocalTransform().getInverse();
            m_localInverseTransformNeedUpdate = false;
        }

        return m_inverseTransform;
    }

    const sf::Transform& Transformable::getGlobalTransform() const {

        if (m_globalTransformNeedUpdate) {

            if (!m_parent.has_value()) {
                m_globalTransform = getLocalTransform();
            } else {
                assert(m_registry);
                const auto* parentTransformPtr = m_registry->tryGet<Transformable>(*m_parent);
                assert(parentTransformPtr);
                m_globalTransform = parentTransformPtr->getGlobalTransform() * getLocalTransform();
            }
        }

        return m_globalTransform;
    }

    void Transformable::addChild(Entity child) {

        assert(std::find(m_children.cbegin(), m_children.cend(), child) == m_children.cend());
        m_children.push_back(child);
    }

    void Transformable::removeChild(Entity child) {

        auto it = std::remove(m_children.begin(), m_children.end(), child);
        assert(it != m_children.end());
        m_children.erase(it, m_children.end());
    }

    void Transformable::localTransformChanged() {

        m_localTransformNeedUpdate = true;
        m_localInverseTransformNeedUpdate = true;

        m_globalTransformNeedUpdate = true;

        assert(m_registry);
        for (Entity e : m_children) {
            auto* childTransformPtr = m_registry->tryGet<Transformable>(e);
            if (childTransformPtr) { // TODO remove invalid entities from child list.
                childTransformPtr->m_globalTransformNeedUpdate = true;
            }
        }
    }
}
