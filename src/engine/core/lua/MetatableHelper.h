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

        template<typename T, typename = void>
        struct metatableInitializer {
            inline static void initializeMetatable(en::LuaState& lua) {}
        };

        template<typename T>
        struct metatableInitializer<T, std::enable_if_t<std::is_invocable_v<decltype(T::initializeMetatable), en::LuaState&>>> {
            inline static void initializeMetatable(en::LuaState& lua) {
                T::initializeMetatable(lua);
            }
        };

        template<typename T>
        inline void initializeMetatable(en::LuaState& lua) {metatableInitializer<T>::initializeMetatable(lua);}
    }

    // Gets or adds a metatable for a given type.
    // Returns true if the metatable did not exist before.
    template<typename T>
    inline bool getMetatable(en::LuaState& lua) {

        if (!luaL_newmetatable(lua, utils::demangle<T>().c_str()))
            return false;

        std::cout << "Created metatable for type " << utils::demangle<T>() << std::endl;

        lua_pushvalue(lua, -1);
        lua_setfield(lua, -2, "__index");
        detail::initializeMetatable<T>(lua);

        return true;
    }
}

#endif //SAXION_Y2Q2_RENDERING_METATABLE_HELPER_H
