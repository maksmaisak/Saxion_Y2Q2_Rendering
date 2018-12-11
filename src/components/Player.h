//
// Created by Maksym Maisak on 24/10/18.
//

#ifndef SAXION_Y2Q1_CPP_PLAYER_H
#define SAXION_Y2Q1_CPP_PLAYER_H

#include <SFML/System.hpp>
#include "Entity.h"
#include "ParticleSystem.h"

struct Player {

    float acceleration = 800.f;
    float maxSpeed = 1000.f;
    float drag = 50.f;
    float rotationSpeed = 360.f;

    sf::Time shootInterval = sf::seconds(0.25f);
    sf::Time timeWhenCanShootAgain = sf::Time::Zero;

    // TEMP Hacky
    ParticleSystem* exhaustParticleSystem = nullptr;
};

#endif //SAXION_Y2Q1_CPP_PLAYER_H
