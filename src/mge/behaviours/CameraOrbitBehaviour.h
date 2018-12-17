//
// Created by Maksym Maisak on 16/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_CAMERAORBITBEHAVIOUR_H
#define SAXION_Y2Q2_RENDERING_CAMERAORBITBEHAVIOUR_H

#include "AbstractBehaviour.hpp"
#include <SFML/System.hpp>

class CameraOrbitBehaviour : public AbstractBehaviour {

public:
    CameraOrbitBehaviour(GameObject* target, float distance = 10.f, float minTilt = -90.f, float maxTilt = 90.f, float rotationSpeed = 0.1f);
    void update(float dt) override;

private:
    GameObject* m_target;

    float m_distance;
    float m_minTilt;
    float m_maxTilt;
    float m_rotationSpeed;

    sf::Vector2i m_previousMousePosition;
};


#endif //SAXION_Y2Q2_RENDERING_CAMERAORBITBEHAVIOUR_H
