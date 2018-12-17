//
// Created by Maksym Maisak on 16/12/18.
//

#include "CameraOrbitBehaviour.h"
#include <SFML/Window.hpp>
#include "glm.hpp"
#include "glm/gtc/epsilon.hpp"
#include "glm/gtx/vector_angle.hpp"
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
    m_rotationSpeed(rotationSpeed)
{
    m_previousMousePosition = sf::Mouse::getPosition();
}

void CameraOrbitBehaviour::update(float dt) {

    if (!m_target) return;

    sf::Vector2i input = updateMouseInput();

    glm::vec3 targetPosition = m_target->getWorldPosition();
    glm::vec3 offsetDirection = glm::normalize(_owner->getLocalPosition() - targetPosition);
    if (glm::any(glm::isnan(offsetDirection))) offsetDirection = glm::vec3(0, 0, 1);
    offsetDirection = glm::rotate(offsetDirection, -input.x * m_rotationSpeed * dt, glm::vec3(0, 1, 0));

    glm::vec3 flatOffsetDirection = glm::normalize(glm::vec3(offsetDirection.x, 0, offsetDirection.z));
    if (glm::any(glm::isnan(flatOffsetDirection))) flatOffsetDirection = glm::vec3(0, 0, 1);
    glm::vec3 right = glm::cross(glm::vec3(0, 1, 0), flatOffsetDirection);

    float elevationAngle = glm::orientedAngle(offsetDirection, flatOffsetDirection, right);
    elevationAngle -= input.y * m_rotationSpeed * dt;
    elevationAngle = glm::clamp(elevationAngle, glm::radians(m_minTilt), glm::radians(m_maxTilt));
    offsetDirection = glm::rotate(flatOffsetDirection, -elevationAngle, right);

    glm::vec3 forward = offsetDirection;
    glm::vec3 up = glm::cross(forward, right);
    _owner->setTransform(glm::mat4(
        glm::vec4(right, 0),
        glm::vec4(up, 0),
        glm::vec4(offsetDirection, 0),
        glm::vec4(targetPosition + offsetDirection * m_distance, 1)
    ));
}

sf::Vector2i CameraOrbitBehaviour::updateMouseInput() {

    sf::Vector2i currentMousePosition = sf::Mouse::getPosition();
    sf::Vector2i deltaMousePosition = currentMousePosition - m_previousMousePosition;
    m_previousMousePosition = currentMousePosition;

    return deltaMousePosition;
}
