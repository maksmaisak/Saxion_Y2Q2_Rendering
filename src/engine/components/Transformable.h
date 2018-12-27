//
// Created by Maksym Maisak on 22/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_TRANSFORMABLE_H
#define SAXION_Y2Q2_RENDERING_TRANSFORMABLE_H

#include <vector>
#include "glm.hpp"
#include <glm/gtc/quaternion.hpp>

#include "Entity.h"
#include "Behavior.h"

namespace en {

    class Engine;
    class EntityRegistry;

    class Transformable final {

        friend class TransformableHierarchySystem;

    public:

        Transformable() = default;

        const glm::mat4& getLocalTransform() const;
        const glm::mat4& getWorldTransform() const;

        inline const glm::vec3& getLocalPosition() const {return m_position;}
        inline const glm::quat& getLocalRotation() const {return m_rotation;}
        inline const glm::vec3& getLocalScale   () const {return m_scale;}
        inline       Entity     getParent       () const {return m_parent;}
        inline const std::vector<Entity>& getChildren() const {return m_children;}

        glm::vec3 getWorldPosition() const;
        glm::quat getWorldRotation() const;

        void setLocalPosition(const glm::vec3& localPosition);
        void setLocalRotation(const glm::quat& localRotation);
        void setLocalScale   (const glm::vec3& localScale);
        void setParent       (Entity newParent);

        void move  (const glm::vec3& offset);
        void rotate(const glm::quat& offset);
        void rotate(float angle, const glm::vec3& axis);
        void scale (const glm::vec3& scale);

    private:

        void addChild(Entity child);
        void removeChild(Entity child);

        EntityRegistry* m_registry = nullptr;
        Entity m_entity = en::nullEntity;
        Entity m_parent = en::nullEntity;
        std::vector<Entity> m_children;

        glm::vec3 m_position = {0, 0, 0};
        glm::quat m_rotation = {1, 0, 0, 0};
        glm::vec3 m_scale    = {1, 1, 1};

        mutable glm::mat4 m_matrixLocal = glm::mat4(1.f);
        mutable bool m_matrixLocalDirty = true;

        mutable glm::mat4 m_matrixWorld = glm::mat4(1.f);
        mutable bool m_matrixWorldDirty = true;

        void makeDirty();
    };
}

#endif //SAXION_Y2Q2_RENDERING_TRANSFORMABLE_H
