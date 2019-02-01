//
// Created by Maksym Maisak on 24/10/18.
//

#ifndef SAXION_Y2Q1_CPP_BEHAVIORSYSTEM_H
#define SAXION_Y2Q1_CPP_BEHAVIORSYSTEM_H

#include <typeindex>
#include <type_traits>
#include <SFML/Graphics.hpp>
#include <vector>

#include "System.h"
#include "Behavior.h"
#include "EntityEvents.h"

namespace en {

    template<typename TBehavior>
    class BehaviorSystem : public System, Receiver<ComponentAdded<TBehavior>> {

        static_assert(std::is_base_of_v<Behavior, TBehavior>);

        inline void update(float dt) override {

            for (Entity e : m_notStarted) {

                auto* behavior = m_registry->tryGet<TBehavior>(e);
                if (behavior) {
                    behavior->start();
                }
            }
            m_notStarted.clear();

            for (Entity e : m_registry->with<TBehavior>()) {

                auto& behavior = m_registry->get<TBehavior>(e);
                behavior.update(dt);
            }
        }

        inline void draw() override {

            for (Entity e : m_registry->with<TBehavior>()) {

                auto& behavior = m_registry->get<TBehavior>(e);
                behavior.draw();
            }
        }

        inline void receive(const ComponentAdded<TBehavior>& info) override {

            m_notStarted.emplace_back(info.entity);
        }

        std::vector<Entity> m_notStarted;
    };
}


#endif //SAXION_Y2Q1_CPP_BEHAVIORSYSTEM_H
