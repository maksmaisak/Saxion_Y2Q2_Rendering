//
// Created by Maksym Maisak on 2019-01-29.
//

#ifndef SAXION_Y2Q2_RENDERING_COMPONENTREFERENCE_H
#define SAXION_Y2Q2_RENDERING_COMPONENTREFERENCE_H

#include "EntityRegistry.h"
#include "MetatableHelper.h"

namespace en {

    /// When components are removed, other components are moved around to maintain memory contiguity,
    /// so maintaining pointers to components is not viable.
    /// This is an alternative to a pointer to a component of an entity that fixes that.
    /// A wrapper class around a pointer to the registry and an entity.
    /// Implicitly converts to a pointer to the component.
    template<typename T>
    class ComponentReference {

    public:

        inline static void initializeEmptyMetatable(LuaState& lua) {

            getMetatable<T>(lua);
            lua_setmetatable(lua, -2);

            lua_pushcfunction(lua, &lua::detail::indexFunction);
            lua_setfield(lua, -2, "__index");

            lua_pushcfunction(lua, &lua::detail::newindexFunction);
            lua_setfield(lua, -2, "__newindex");
        }

        inline ComponentReference(EntityRegistry& registry, Entity entity) : m_registry(&registry), m_entity(entity) {

            assert(!isNullEntity(entity));
        }

        inline operator T&() {
            return *m_registry->tryGet<T>(m_entity);
        }

        inline operator T*() {
            return m_registry->tryGet<T>(m_entity);
        }

        inline T* operator->() {
            return operator T*();
        }

    private:

        EntityRegistry* m_registry;
        Entity m_entity;
    };
}

#endif //SAXION_Y2Q2_RENDERING_COMPONENTREFERENCE_H
