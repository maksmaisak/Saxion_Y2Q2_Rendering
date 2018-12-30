//
// Created by Maksym Maisak on 29/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_LUASTACK_H
#define SAXION_Y2Q2_RENDERING_LUASTACK_H

#include <type_traits>
#include <lua/lua.hpp>
#include <string>
#include <optional>

namespace lua {

    template<typename T, typename = void>
    struct toAdapter;

    template<>
    struct toAdapter<bool> {
        bool operator()(lua_State* L, int index = -1) { return lua_toboolean(L, index); }
    };

    template<typename T>
    struct toAdapter<T, std::enable_if_t<std::is_integral_v<T>>> {
        T operator()(lua_State* L, int index = -1) { return lua_tointeger(L, index); }
    };

    template<typename T>
    struct toAdapter<T, std::enable_if_t<std::is_floating_point_v<T>>> {
        T operator()(lua_State* L, int index = -1) { return lua_tonumber(L, index); }
    };

    template<>
    struct toAdapter<std::string> {
        std::string operator()(lua_State* L, int index = -1) { return lua_tostring(L, index); }
    };

    class PopperOnDestruct {

    public:
        inline PopperOnDestruct(lua_State* luaState) : L(luaState) {}
        inline ~PopperOnDestruct() {lua_pop(L, 1);}

    private:
        lua_State* L;
    };
}

#endif //SAXION_Y2Q2_RENDERING_LUASTACK_H
