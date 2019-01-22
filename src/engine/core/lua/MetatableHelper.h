//
// Created by Maksym Maisak on 3/1/19.
//

#ifndef SAXION_Y2Q2_RENDERING_METATABLE_HELPER_H
#define SAXION_Y2Q2_RENDERING_METATABLE_HELPER_H

#include "LuaState.h"
#include "LuaStack.h"
#include "ClosureHelper.h"
#include "Meta.h"
#include "Demangle.h"
#include <functional>
#include <vector>

namespace lua {

    namespace detail {

        /// The __index function: (table, key) -> value
        /// Try using a property getter from __getters, otherwise look it up in the metatable
        int indexFunction(lua_State* L);

        /// The __index function: (table, key, value) -> ()
        /// Try using a property setter from __setters, otherwise just rawset it
        int newindexFunction(lua_State* L);
    }

    // Gets or adds a metatable for a given type.
    // Returns true if the metatable did not exist before.
    template<typename T>
    inline bool getMetatable(en::LuaState& lua) {

        if (!luaL_newmetatable(lua, utils::demangle<T>().c_str()))
            return false;

        std::cout << "Created metatable for type " << utils::demangle<T>() << std::endl;

        lua_newtable(lua);
        lua_setfield(lua, -2, "__getters");

        lua_newtable(lua);
        lua_setfield(lua, -2, "__setters");

        lua_pushcfunction(lua, &detail::indexFunction);
        lua_setfield(lua, -2, "__index");

        lua_pushcfunction(lua, &detail::newindexFunction);
        lua_setfield(lua, -2, "__newindex");

        if constexpr (std::is_pointer_v<T>) {
            lua.setField("__eq", [](T a, T b) { return a == b; });
        }

        return true;
    }

    template<typename T, typename Owner = struct NoOwner>
    class Property {

    public:

        using Getter = std::conditional_t<
            std::is_same_v<Owner, NoOwner>,
            std::function<T()>,
            std::function<T(Owner&)>
        >;

        using Setter = std::conditional_t<
            std::is_same_v<Owner, NoOwner>,
            std::function<void(T&&)>,
            std::function<void(Owner&, T&&)>
        >;

        using UnderlyingOwner = std::remove_pointer_t<utils::remove_cvref_t<Owner>>;

        inline Property(T UnderlyingOwner::* memberPtr) :
            m_getter([memberPtr](Owner& owner){
                if constexpr (std::is_pointer_v<Owner>)
                    return *owner.*memberPtr;
                else
                    return owner.*memberPtr;
            }),
            m_setter([memberPtr](Owner& owner, T&& value){
                if constexpr (std::is_pointer_v<Owner>)
                    *owner.*memberPtr = std::forward<T>(value);
                else
                    owner.*memberPtr = std::forward<T>(value);
            })
            {}

        inline Property(const T UnderlyingOwner::* memberPtr) :
            m_getter([memberPtr](Owner& owner){
                if constexpr (std::is_pointer_v<Owner>)
                    return *owner.*memberPtr;
                else
                    return owner.*memberPtr;
            })
            {}

        inline Property(const Getter& getter, const Setter& setter) : m_getter(getter), m_setter(setter) {}
        inline Property(const Getter& getter) : m_getter(getter) {}

        inline bool hasGetter() const {return m_getter.operator bool();};
        inline bool hasSetter() const {return m_setter.operator bool();};

        inline const Getter& getGetter() const {return m_getter;}
        inline const Setter& getSetter() const {return m_setter;}

    private:
        Getter m_getter = {};
        Setter m_setter = {};
    };

    /// Adds a getter and setter, if present, to the __getter and __setter tables in the table on top of stack.
    /// That table is assumed to be a metatable.
    template<typename Owner, typename T>
    inline void addProperty(lua_State* L, const std::string& name, const Property<Owner, T>& property) {

        if (property.hasGetter()) {

            auto popGetters = PopperOnDestruct(L);
            lua_getfield(L, -1, "__getters");

            ClosureHelper::makeClosure(L, property.getGetter());
            lua_setfield(L, -2, name.c_str());
        }

        if (property.hasSetter()) {

            auto popSetters = PopperOnDestruct(L);
            lua_getfield(L, -1, "__setters");

            ClosureHelper::makeClosure(L, property.getSetter());
            lua_setfield(L, -2, name.c_str());
        }
    }
}

#endif //SAXION_Y2Q2_RENDERING_METATABLE_HELPER_H
