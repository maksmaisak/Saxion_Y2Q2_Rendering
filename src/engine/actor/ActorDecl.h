//
// Created by Maksym Maisak on 24/10/18.
//

#ifndef SAXION_Y2Q1_CPP_ACTORDECL_H
#define SAXION_Y2Q1_CPP_ACTORDECL_H

#include <type_traits>
#include "Entity.h"
#include "EntityRegistry.h"

namespace en {

    class Behavior;
    class Engine;

    template<typename T>
    constexpr inline bool isBehavior = std::is_base_of<Behavior, T>::value;

    /// A thin wrapper around an entity. Facilitates GameObject-like programming.
    class Actor final {

    public:
        Actor(Engine& engine, Entity entity);

        /// Adds a non-behavior component
        template<typename TComponent, typename... Args>
        std::enable_if_t<!isBehavior<TComponent>, TComponent&>
        add(Args&&... args);

        /// Adds a behavior component.
        template<typename TBehavior, typename... Args>
        std::enable_if_t<isBehavior<TBehavior>, TBehavior&>
        add(Actor& actor, Args&&... args);

        /// Adds a behavior component with the first parameter (actor) omitted.
        template<typename TBehavior, typename... Args>
        std::enable_if_t<isBehavior<TBehavior>, TBehavior&>
        add(Args&&... args);

        template<typename TComponent>
        inline TComponent& get() {return m_registry->get<TComponent>(m_entity);}

        template<typename TComponent>
        inline TComponent* tryGet() {return m_registry->tryGet<TComponent>(m_entity);}

        template<typename TComponent>
        inline TComponent& remove() {return m_registry->remove<TComponent>(m_entity);}

        inline Engine& getEngine() {return *m_engine;}
        inline operator Entity() {return m_entity;}

    private:
        Engine* m_engine;
        EntityRegistry* m_registry;
        Entity m_entity;
    };
}


#endif //SAXION_Y2Q1_CPP_ACTORDECL_H
