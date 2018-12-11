//
// Created by Maksym Maisak on 21/10/18.
//

#ifndef SAXION_Y2Q1_CPP_ACTOR_H
#define SAXION_Y2Q1_CPP_ACTOR_H

#include <memory>
#include <vector>
#include <unordered_set>
#include <SFML/Graphics.hpp>
#include "Engine.h"

// The declaration is here to make it possible to include only the declaration,
// in case you need just the non-templated stuff.
#include "ActorDecl.h"

namespace en {

    template<typename TBehavior, typename... Args>
    std::enable_if_t<isBehavior<TBehavior>, TBehavior&>
    Actor::add(Actor& actor, Args&& ... args) {

        assert(&actor == this);

        m_engine->ensureBehaviorSystem<TBehavior>();
        auto& behavior = m_registry->add<TBehavior>(m_entity, actor, std::forward<Args>(args)...);
        behavior.start();

        return behavior;
    }

    template<typename TBehavior, typename... Args>
    std::enable_if_t<isBehavior<TBehavior>, TBehavior&>
    Actor::add(Args&& ... args) {
        return add<TBehavior>(*this, std::forward<Args>(args)...);
    }

    template<typename TComponent, typename... Args>
    std::enable_if_t<!isBehavior<TComponent>, TComponent&>
    Actor::add(Args&& ... args) {
        return m_registry->add<TComponent>(m_entity, std::forward<Args>(args)...);
    }
}


#endif //SAXION_Y2Q1_CPP_ACTOR_H
