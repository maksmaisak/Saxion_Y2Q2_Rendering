//
// Created by Maksym Maisak on 17/10/18.
//

#ifndef SAXION_Y2Q1_CPP_RIGIDBODY_H
#define SAXION_Y2Q1_CPP_RIGIDBODY_H

#include "glm.hpp"

namespace en {

    struct Rigidbody {

        bool isKinematic = false;
        glm::vec3 velocity;
        float invMass = 1.f;
        float bounciness = 1.f;

        float radius = 1.f;
    };
}

#endif //SAXION_Y2Q1_CPP_RIGIDBODY_H
