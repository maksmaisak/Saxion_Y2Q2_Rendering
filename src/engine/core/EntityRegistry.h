//
// Created by Maksym Maisak on 21/10/18.
//

#ifndef SAXION_Y2Q1_CPP_ENTITYREGISTRY_H
#define SAXION_Y2Q1_CPP_ENTITYREGISTRY_H

#include <memory>
#include <utility>
#include <set>
#include <iostream>
#include "Entity.h"
#include "ComponentPool.h"
#include "EntitiesView.h"
#include "Messaging.h"
#include "EntityEvents.h"
#include "Entities.h"
#include "Transformable.h"
#include "CustomTypeIndex.h"

namespace en {

    /// Manages entities and components
    /// Create, destroy entities.
    /// Add, modify and remove components.
    /// Iterate through entities with a given component set.
    class EntityRegistry {

    public:

        en::Entity makeEntity();
        void destroy(Entity entity);
        void destroyAll();

        template<class TComponent>
        inline TComponent& get(Entity entity) const;

        template<class TComponent>
        inline TComponent* tryGet(Entity entity) const;

        template<class TComponent, typename... Args>
        inline TComponent& add(Entity entity, Args&& ... args);

        template<class TComponent>
        inline TComponent& remove(Entity entity);

        template<typename... TComponent>
        inline EntitiesView<TComponent...> with();

    private:

        Entities m_entities;

        using componentTypeIndices = CustomTypeIndex<struct componentIndicesDummy>;
        mutable std::vector<std::unique_ptr<ComponentPoolBase>> m_componentPools;

        template<typename TComponent>
        inline ComponentPool<TComponent>& getPool(bool mustBePresentAlready = false) const;
    };

    template<class TComponent>
    inline TComponent& EntityRegistry::get(const en::Entity entity) const {

        ComponentPool<TComponent>& pool = getPool<TComponent>(true);
        return pool.get(entity);
    }

    template<class TComponent>
    inline TComponent* EntityRegistry::tryGet(Entity entity) const {

        ComponentPool<TComponent>& pool = getPool<TComponent>();
        return pool.tryGet(entity);
    }

    template<class TComponent, typename... Args>
    inline TComponent& EntityRegistry::add(Entity entity, Args&& ... args) {

        ComponentPool<TComponent>& pool = getPool<TComponent>();

        auto [index, componentReference] = pool.insert(entity, std::forward<Args>(args)...);
        Receiver<ComponentAdded<TComponent>>::accept({entity, componentReference});

        return componentReference;
    }

    template<typename... TComponent>
    inline EntitiesView<TComponent...> EntityRegistry::with() {

        return EntitiesView<TComponent...>(getPool<TComponent>()...);
    }

    template<class TComponent>
    inline TComponent& EntityRegistry::remove(Entity entity) {
        getPool<TComponent>(true).remove(entity);
    }

    template<typename TComponent>
    inline ComponentPool<TComponent>& EntityRegistry::getPool(bool mustBePresentAlready) const {

        const std::size_t index = componentTypeIndices::index<TComponent>;

        if (index >= m_componentPools.size()) {
            m_componentPools.resize(index + 1);
        }

        if (!m_componentPools[index]) {

            assert(!mustBePresentAlready);
            m_componentPools[index] = std::make_unique<ComponentPool<TComponent>>();
            //std::clog << "Created a component pool (index " << index << ") for " << typeid(TComponent).name() << std::endl;
        }

        return *static_cast<ComponentPool<TComponent>*>(m_componentPools[index].get());
    }
}

#endif //SAXION_Y2Q1_CPP_ENTITYREGISTRY_H
