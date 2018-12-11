//
// Created by Maksym Maisak on 23/10/18.
//

#ifndef SAXION_Y2Q1_CPP_FLICKERSYSTEM_H
#define SAXION_Y2Q1_CPP_FLICKERSYSTEM_H

#include "Engine.h"
#include "MyMath.h"
#include "EntityRegistry.h"
#include "Flicker.h"

class FlickerSystem : public en::System {



public:

    void update(float dt) override {

        auto view = m_registry->with<Flicker>();
        for (en::Entity e : m_registry->with<Flicker>()) {
            m_registry->get<Flicker>(e).m_shape->setOutlineThickness(en::random(2.f, 4.f));
        }
    }
};

#endif //SAXION_Y2Q1_CPP_FLICKERSYSTEM_H
