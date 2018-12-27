//
// Created by Maksym Maisak on 22/12/18.
//

#include "Transformable.h"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/vector_query.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace en {

    const glm::mat4& Transformable::getLocalTransform() const {

        if (m_matrixLocalDirty) {
            m_matrixLocal = glm::translate(m_position) * glm::toMat4(m_rotation) * glm::scale(m_scale);
            m_matrixLocalDirty = false;
        }

        return m_matrixLocal;
    }

    const glm::mat4& Transformable::getWorldTransform() const {

        if (m_matrixWorldDirty) {

            if (!en::isNullEntity(m_parent)) {
                m_matrixWorld = m_registry->get<Transformable>(m_parent).getLocalTransform() * getLocalTransform();
            } else {
                m_matrixWorld = getLocalTransform();
            }

            m_matrixWorldDirty = false;
        }

        return m_matrixWorld;
    }

    void Transformable::setLocalPosition(const glm::vec3& localPosition) {

        m_position = localPosition;
        makeDirty();
    }

    void Transformable::setLocalRotation(const glm::quat& localRotation) {

        m_rotation = localRotation;
        makeDirty();
    }

    void Transformable::setLocalScale(const glm::vec3& localScale) {

        m_scale = localScale;
        makeDirty();
    }

    void Transformable::setParent(Entity newParent) {

        Entity oldParent = m_parent;
        if (!en::isNullEntity(oldParent)) {
            if (oldParent == newParent) return;
            m_registry->get<Transformable>(oldParent).removeChild(m_entity);
        }

        if (!isNullEntity(newParent)) {
            auto& parentTransformable = m_registry->get<Transformable>(newParent);
            parentTransformable.addChild(m_entity);
        }

        m_parent = newParent;
        m_matrixWorldDirty = true;
    }

    void Transformable::makeDirty() {

        m_matrixLocalDirty = true;
        m_matrixWorldDirty = true;
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

    void Transformable::move(const glm::vec3& offset) {

        m_position += offset;
        makeDirty();
    }

    void Transformable::rotate(const glm::quat& offset) {

        m_rotation = offset * m_rotation;
        makeDirty();
    }

    void Transformable::rotate(float angle, const glm::vec3& axis) {

        rotate(glm::angleAxis(angle, glm::normalize(axis)));
    }

    void Transformable::scale(const glm::vec3& scale) {

        m_scale *= scale;
        makeDirty();
    }

    glm::vec3 Transformable::getWorldPosition() const {
        return glm::vec3(getWorldTransform()[3]);
    }

    glm::quat Transformable::getWorldRotation() const {

        glm::vec3 scale;
        glm::quat orientation;
        glm::vec3 translation;
        glm::vec3 skew;
        glm::vec4 perspective;
        glm::decompose(getWorldTransform(), scale, orientation, translation, skew, perspective);

        return orientation;
    }
}
