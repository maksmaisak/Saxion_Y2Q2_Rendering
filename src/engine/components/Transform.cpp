//
// Created by Maksym Maisak on 22/12/18.
//

#include "Transform.h"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/vector_query.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace en {

    const glm::mat4& Transform::getLocalTransform() const {

        if (m_matrixLocalDirty) {
            m_matrixLocal = glm::translate(m_position) * glm::toMat4(m_rotation) * glm::scale(m_scale);
            m_matrixLocalDirty = false;
        }

        return m_matrixLocal;
    }

    const glm::mat4& Transform::getWorldTransform() const {

        if (m_matrixWorldDirty) {

            if (!en::isNullEntity(m_parent)) {
                m_matrixWorld = m_registry->get<Transform>(m_parent).getWorldTransform() * getLocalTransform();
            } else {
                m_matrixWorld = getLocalTransform();
            }

            m_matrixWorldDirty = false;
        }

        return m_matrixWorld;
    }

    Transform& Transform::setLocalPosition(const glm::vec3& localPosition) {

        m_position = localPosition;
        markDirty();
        return *this;
    }

    Transform& Transform::setLocalRotation(const glm::quat& localRotation) {

        m_rotation = localRotation;
        markDirty();
        return *this;
    }

    Transform& Transform::setLocalScale(const glm::vec3& localScale) {

        m_scale = localScale;
        markDirty();
        return *this;
    }

    // TODO Make this preserve world position
    Transform& Transform::setParent(Entity newParent) {

        Entity oldParent = m_parent;
        if (!isNullEntity(oldParent)) {
            if (oldParent == newParent) return *this;
            m_registry->get<Transform>(oldParent).removeChild(m_entity);
        }

        if (!isNullEntity(newParent)) {
            auto& parentTransformable = m_registry->get<Transform>(newParent);
            parentTransformable.addChild(m_entity);
        }

        m_parent = newParent;
        m_matrixWorldDirty = true;
        return *this;
    }

    void Transform::markDirty() {

        m_matrixLocalDirty = true;
        markWorldDirty();
    }

    void Transform::markWorldDirty() {

        m_matrixWorldDirty = true;

        for (Entity child : m_children) {

            auto* childTf = m_registry->tryGet<Transform>(child);
            if (childTf) childTf->markWorldDirty();
            // TODO remove children with no transform from the list of children
        }
    }

    void Transform::addChild(Entity child) {

        assert(std::find(m_children.cbegin(), m_children.cend(), child) == m_children.cend());
        m_children.push_back(child);
    }

    void Transform::removeChild(Entity child) {

        auto it = std::remove(m_children.begin(), m_children.end(), child);
        assert(it != m_children.end());
        m_children.erase(it, m_children.end());
    }

    Transform& Transform::move(const glm::vec3& offset) {

        m_position += offset;
        markDirty();
        return *this;
    }

    Transform& Transform::rotate(const glm::quat& offset) {

        m_rotation = offset * m_rotation;
        markDirty();
        return *this;
    }

    Transform& Transform::rotate(float angle, const glm::vec3& axis) {

        rotate(glm::angleAxis(angle, glm::normalize(axis)));
        return *this;
    }

    Transform& Transform::scale(const glm::vec3& scale) {

        m_scale *= scale;
        markDirty();
        return *this;
    }

    glm::vec3 Transform::getWorldPosition() const {
        return glm::vec3(getWorldTransform()[3]);
    }

    glm::quat Transform::getWorldRotation() const {

        glm::vec3 scale;
        glm::quat orientation;
        glm::vec3 translation;
        glm::vec3 skew;
        glm::vec4 perspective;
        glm::decompose(getWorldTransform(), scale, orientation, translation, skew, perspective);

        return orientation;
    }

    void Transform::initializeMetatable(LuaState& lua) {

        lua.setField("move", [](Transform* tf, float x, float y, float z) {
            return &tf->move({x, y, z});
        });

        lua.setField("rotate", [](Transform* tf, float angle, float x, float y, float z) {
            return &tf->rotate(glm::radians(angle), {x, y, z});
        });

        lua::addProperty(lua, "position", lua::property(
            [](Transform* tf) {return tf->getLocalPosition();},
            [](Transform* tf, const glm::vec3& pos) {return tf->setLocalPosition(pos);}
        ));

        lua::addProperty(lua, "rotation", lua::property(
            [](Transform* tf) {return glm::degrees(glm::eulerAngles(tf->getLocalRotation()));},
            [](Transform* tf, const glm::vec3& eulerAngles) {return tf->setLocalRotation(glm::radians(eulerAngles));}
        ));

        lua::addProperty(lua, "scale", lua::property(
            [](Transform* tf) {return tf->getLocalScale();},
            [](Transform* tf, const glm::vec3& scale) {return tf->setLocalScale(scale);}
        ));
    }
}
