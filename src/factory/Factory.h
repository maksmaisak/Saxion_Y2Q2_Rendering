//
// Created by Maksym Maisak on 18/10/18.
//

#ifndef SAXION_Y2Q1_CPP_FACTORY_H
#define SAXION_Y2Q1_CPP_FACTORY_H

#include "Engine.h"
#include "Asteroid.h"

namespace game {

    void makeMainLevel(en::Engine& engine);

    en::Entity makePlayer(en::Engine& engine);
    en::Entity makeAsteroid(en::Engine& engine);
    en::Entity makeAsteroid(en::Engine& engine, Asteroid::Size size);
    en::Entity makeAsteroid(en::Engine& engine, Asteroid::Size size, const sf::Vector2f& position, const sf::Vector2f& velocity);
    en::Entity makeBullet(en::Engine& engine, const sf::Vector2f& position, const sf::Vector2f& velocity);
};


#endif //SAXION_Y2Q1_CPP_FACTORY_H
