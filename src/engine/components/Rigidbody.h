//
// Created by Maksym Maisak on 17/10/18.
//

#ifndef SAXION_Y2Q1_CPP_RIGIDBODY_H
#define SAXION_Y2Q1_CPP_RIGIDBODY_H

#include <SFML/Graphics.hpp>

namespace en {

    struct Rigidbody {

        sf::Vector2f velocity;
        float invMass = 1.f;
        float bounciness = 1.f;

        float radius = 10.f;
    };
}

#endif //SAXION_Y2Q1_CPP_RIGIDBODY_H
