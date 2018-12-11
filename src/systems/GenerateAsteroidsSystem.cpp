//
// Created by Maksym Maisak on 30/10/18.
//

#include <iostream>
#include "GenerateAsteroidsSystem.h"
#include "Asteroid.h"
#include "Factory.h"

void GenerateAsteroidsSystem::update(float dt) {

    if (m_registry->with<Asteroid>().count() < m_targetNumAsteroids) {
        game::makeAsteroid(*m_engine);
    }
}
