//
// Created by Maksym Maisak on 29/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_LUASTACK_H
#define SAXION_Y2Q2_RENDERING_LUASTACK_H

#include <type_traits>
#include <lua.hpp>
#include <string>
#include <cstring>
#include <optional>

namespace lua {

    // Default case. Treat everything as userdata
    template<typename T, typename = void>
    struct TypeAdapter {
        static void push(lua_State* L, const T& value) {
            // TODO set __gc in the metatable to the destructor
            void* ptr = lua_newuserdata(L, sizeof(T));
            *static_cast<T*>(ptr) = value;
            // TODO What if the copy assignment operator is doing something with the object being assigned to?
            // Make it use the copy/move constructor instead of copy/move assignment.
            // Maybe some way to custom-allocate with a given address?
        }
        static T& to(lua_State* L, int index = -1) {
            void* ptr = lua_touserdata(L, index);
            return *reinterpret_cast<T*>(ptr);
        }
    };

    template<>
    struct TypeAdapter<bool> {
        static bool is  (lua_State* L, int index = -1) { return lua_isboolean(L, index); }
        static bool to  (lua_State* L, int index = -1) { return lua_toboolean(L, index); }
        static void push(lua_State* L, bool value) { lua_pushboolean(L, value); }
    };

    template<typename T>
    struct TypeAdapter<T, std::enable_if_t<std::is_integral_v<T>>> {
        static bool is  (lua_State* L, int index = -1) { return lua_isinteger(L, index); }
        static T    to  (lua_State* L, int index = -1) { return lua_tointeger(L, index); }
        static void push(lua_State* L, T value) { lua_pushinteger(L, value); }
    };

    template<typename T>
    struct TypeAdapter<T, std::enable_if_t<std::is_floating_point_v<T>>> {
        static bool is  (lua_State* L, int index = -1) { return lua_isnumber(L, index); }
        static T    to  (lua_State* L, int index = -1) { return lua_tonumber(L, index); }
        static void push(lua_State* L, T value) { lua_pushnumber(L, value); }
    };

    template<>
    struct TypeAdapter<std::string> {
        static bool        is  (lua_State* L, int index = -1) { return lua_isstring(L, index); }
        static std::string to  (lua_State* L, int index = -1) { return lua_tostring(L, index); }
        static void        push(lua_State* L, const std::string& value) { lua_pushstring(L, value.c_str()); }
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
