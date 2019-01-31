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

        inline static void initializeMetatable(LuaState& lua) {

            getMetatable<T>(lua);
            lua_setmetatable(lua, -2);

            // Make it use the getters and setters of the metatable of the component type.
            lua_pushnil(lua);
            lua_setfield(lua, -2, "__getters");

            lua_pushnil(lua);
            lua_setfield(lua, -2, "__setters");
        }

        inline ComponentReference(EntityRegistry& registry, Entity entity) : m_registry(&registry), m_entity(entity) {

            assert(!isNullEntity(entity));
        }

        inline operator T&() {
            return checkValid(), *m_registry->tryGet<T>(m_entity);
        }

        inline operator T*() {
            return checkValid(), m_registry->tryGet<T>(m_entity);
        }

        inline T* operator->() {
            return operator T*();
        }

        inline operator bool() {
            return m_registry && m_registry->isAlive(m_entity);
        }

        inline void checkValid() {

            if (!operator bool())
                throw "This ComponentReference to " + utils::demangle<T>() + "is invalid";
        }

        friend inline bool operator==(const ComponentReference<T>& a, const ComponentReference<T>& b) {
            return a.m_registry == b.m_registry && a.m_entity == b.m_entity;
        }

    private:

        EntityRegistry* m_registry;
        Entity m_entity;
    };

}

#endif //SAXION_Y2Q2_RENDERING_COMPONENTREFERENCE_H
