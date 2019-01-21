//
// Created by Maksym Maisak on 3/1/19.
//

#ifndef SAXION_Y2Q2_RENDERING_METATABLE_HELPER_H
#define SAXION_Y2Q2_RENDERING_METATABLE_HELPER_H

#include "LuaState.h"
#include "LuaStack.h"
#include "ClosureHelper.h"
#include "Demangle.h"
#include <functional>
#include <vector>

namespace lua {

    namespace detail {

        /// The __index function: (table, key) -> value
        /// Try using a property getter from __getters, otherwise look it up in the metatable
        inline int indexFunction(lua_State* L) {

            luaL_checkany(L, 1); // table or userdata
            luaL_checkany(L, 2); // key

            bool hasMetatable = lua_getmetatable(L, 1) == 1;
            assert(hasMetatable);

            // get a property getter from metatable.__getters
            lua_getfield(L, -1, "__getters");
            lua_pushvalue(L, 2);
            lua_gettable(L, -2);

            if (lua_isnil(L, -1)) {

                lua_pop(L, 2); // remove __getters, nil
                lua_pushvalue(L, 2);
                lua_gettable(L, -2); // get from metatable

                lua_remove(L, -2); // remove metatable

                return 1;
            }

            lua_remove(L, -2); // remove __getters

            // call the getter
            lua_pushvalue(L, 1); // table
            lua_pushvalue(L, 2); // key
            lua_pcall(L, 2, 1, 0); // getter(table, key)

            lua_remove(L, -2); // remove metatable

            return 1;
        }

        /// The __index function: (table, key, value) -> ()
        /// Try using a property setter from __setters, otherwise just rawset it
        inline int newindexFunction(lua_State* L) {

            luaL_checkany(L, 1); // table or userdata
            luaL_checkany(L, 2); // key
            luaL_checkany(L, 3); // value

            bool hasMetatable = lua_getmetatable(L, 1) == 1;
            assert(hasMetatable);

            // get a property setter from metatable.__setter
            lua_getfield(L, -1, "__setters");
            lua_pushvalue(L, 2);
            lua_gettable(L, -2);

            if (lua_isnil(L, -1)) {

                lua_pop(L, 3); // remove metatable, __setters, nil
                lua_pushvalue(L, 2);
                lua_pushvalue(L, 3);
                lua_rawset(L, -3); // set

                return 0;
            }

            lua_remove(L, -2); // remove __setters

            lua_pushvalue(L, 1); // table
            lua_pushvalue(L, 3); // value
            lua_pcall(L, 2, 0, 0);

            lua_remove(L, -2); // remove the metatable

            return 0;
        }
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
            std::function<T(const Owner&)>
        >;

        using Setter = std::conditional_t<
            std::is_same_v<Owner, NoOwner>,
            std::function<void(T&&)>,
            std::function<void(Owner&, T&&)>
        >;

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
