//
// Created by Maksym Maisak on 22/10/18.
//

#ifndef SAXION_Y2Q1_CPP_TRANSFORM_H
#define SAXION_Y2Q1_CPP_TRANSFORM_H

#include <vector>
#include <optional>
#include <SFML/Graphics.hpp>
#include "Entity.h"

namespace en {

    class Engine;
    class EntityRegistry;

    /// An exact copy of SFML's sf::Transformable, but with transform hierarchy support.
    class Transformable final {

        friend class Engine;
        friend class TransformableHierarchySystem;

    public:

        Transformable();

        void setPosition(float x, float y);
        void setPosition(const sf::Vector2f& position);
        void setRotation(float angle);
        void setScale(float factorX, float factorY);
        void setScale(const sf::Vector2f& factors);
        void setOrigin(float x, float y);
        void setOrigin(const sf::Vector2f& origin);

        const sf::Vector2f& getPosition() const;
        float getRotation() const;
        const sf::Vector2f& getScale() const;
        const sf::Vector2f& getOrigin() const;

        void move(float offsetX, float offsetY);
        void move(const sf::Vector2f& offset);
        void rotate(float angle);
        void scale(float factorX, float factorY);
        void scale(const sf::Vector2f& factor);

        const sf::Transform& getLocalTransform() const;
        const sf::Transform& getInverseLocalTransform() const;
        const sf::Transform& getGlobalTransform()  const;

        inline const std::optional<Entity>& getParent() const {return m_parent;}
        inline const std::vector<Entity>& getChildren() const {return m_children;}

    private:

        sf::Vector2f          m_origin;                          ///< Origin of translation/rotation/scaling of the object
        sf::Vector2f          m_position;                        ///< Position of the object in the 2D world
        float                 m_rotation;                        ///< Orientation of the object, in degrees
        sf::Vector2f          m_scale;                           ///< Scale of the object

        mutable sf::Transform m_transform;                       ///< Combined transformation of the object
        mutable bool          m_localTransformNeedUpdate;        ///< Does the transform need to be recomputed?

        mutable sf::Transform m_inverseTransform;                ///< Combined transformation of the object
        mutable bool          m_localInverseTransformNeedUpdate; ///< Does the transform need to be recomputed?

        mutable sf::Transform m_globalTransform;
        mutable bool m_globalTransformNeedUpdate = false;

        EntityRegistry* m_registry;
        mutable std::optional<Entity> m_parent;
        mutable std::vector<Entity> m_children;

        void addChild(Entity child);
        void removeChild(Entity child);

        void localTransformChanged();
    };
}

#endif //SAXION_Y2Q1_CPP_TRANSFORM_H
