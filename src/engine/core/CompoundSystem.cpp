//
// Created by Maksym Maisak on 2019-03-08.
//

#include "CompoundSystem.h"

using namespace en;

void CompoundSystem::start() {

    for (auto& system : m_systems)
        system->start();
}

void CompoundSystem::update(float dt) {

    for (auto& system : m_systems)
        system->update(dt);
}

void CompoundSystem::draw() {

    for (auto& system : m_systems)
        system->draw();
}
