//
// Created by Maksym Maisak on 21/10/18.
//

#include "EntityRegistry.h"
#include "Messaging.h"
#include "EntityEvents.h"

namespace en {

    Entity EntityRegistry::makeEntity() {

        const en::Entity entity = m_entities.add();
        Receiver<EntityCreated>::accept({entity});
        return entity;
    }

    void EntityRegistry::destroy(Entity entity) {

        if (!m_entities.contains(entity)) return;

        Receiver<EntityWillBeDestroyed>::accept({entity});

        m_entities.remove(entity);

        for (const auto& poolPtr : m_componentPools) {
            if (poolPtr) {
                poolPtr->remove(entity);
                assert(!poolPtr->contains(entity));
            }
        }
    }

    void EntityRegistry::destroyAll() {

        for (Entity e : m_entities) Receiver<EntityWillBeDestroyed>::accept({e});
        m_entities.clear();

        for (const auto& poolPtr : m_componentPools) {
            if (poolPtr) {
                poolPtr->clear();
            }
        }
    }
}