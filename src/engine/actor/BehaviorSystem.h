//
// Created by Maksym Maisak on 24/10/18.
//

#ifndef SAXION_Y2Q1_CPP_BEHAVIORSYSTEM_H
#define SAXION_Y2Q1_CPP_BEHAVIORSYSTEM_H

#include <typeindex>
#include <type_traits>
#include <SFML/Graphics.hpp>

#include "System.h"
#include "Behavior.h"

namespace en {

    template<typename TBehavior>
    class BehaviorSystem : public System {

        static_assert(std::is_base_of_v<Behavior, TBehavior>);

        void update(float dt) override {

            for (Entity e : m_registry->with<TBehavior>()) m_registry->get<TBehavior>(e).update(dt);
        }

        void draw() override {

            for (Entity e : m_registry->with<TBehavior>()) m_registry->get<TBehavior>(e).draw();
        }
    };
}


#endif //SAXION_Y2Q1_CPP_BEHAVIORSYSTEM_H
