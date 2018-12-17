//
// Created by Maksym Maisak on 16/12/18.
//

#include "CameraOrbitBehaviour.h"
#include <SFML/Window.hpp>
#include "glm.hpp"
#include "mge/core/GameObject.hpp"

CameraOrbitBehaviour::CameraOrbitBehaviour(
    GameObject* target,
    float distance,
    float minTilt,
    float maxTilt,
    float rotationSpeed
) :
    m_target(target),
    m_distance(distance),
    m_minTilt(minTilt),
    m_maxTilt(maxTilt),
    m_rotationSpeed(rotationSpeed) {}

void CameraOrbitBehaviour::update(float dt) {

    if (!m_target) return;

    glm::vec3 targetPosition = m_target->getWorldPosition();
    glm::vec3 offset = _owner->getLocalPosition() - targetPosition;

    auto targetToSelf = glm::normalize(offset);
    if (glm::any(glm::isnan(targetToSelf))) targetToSelf = glm::vec3(0, 0, 1);
    offset = targetToSelf * m_distance;

    float inputX = 0.0f;
    float inputY = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        inputX += m_rotationSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        inputX -= m_rotationSpeed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        inputY += m_rotationSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        inputY -= m_rotationSpeed;
    }

    offset = glm::rotate(offset, inputX * dt, glm::vec3(0, 1, 0));
    offset = glm::rotate(offset, inputY * dt, glm::normalize(glm::cross(glm::vec3(0, 1, 0), offset)));

    auto forward = glm::normalize(offset);
    auto right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), forward));
    auto up = glm::cross(forward, right);

    _owner->setTransform(glm::mat4(
        glm::vec4(right, 0),
        glm::vec4(up, 0),
        glm::vec4(forward, 0),
        glm::vec4(targetPosition + offset, 1)
    ));
}
