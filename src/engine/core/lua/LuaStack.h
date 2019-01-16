//
// Created by Maksym Maisak on 29/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_LUASTACK_H
#define SAXION_Y2Q2_RENDERING_LUASTACK_H

#include <type_traits>
#include <lua.hpp>
#include <string>
#include <optional>
#include <iostream>

#include "Demangle.h"
#include "FunctionTraits.h"

namespace lua {

    // Default case. Treat everything as userdata
    template<typename T, typename = void>
    struct TypeAdapter {

        inline static void push(lua_State* L, const T& value) {

            void* ptr = lua_newuserdata(L, sizeof(T));
            T* valuePtr = new(ptr) T(value); // copy-construct in place.

            if (luaL_newmetatable(L, utils::demangle<T>().c_str())) {

                lua_pushvalue(L, -1);
                lua_setfield(L, -2, "__index");
                std::cout << "Created metatable for type " << utils::demangle<T>() << std::endl;
            }

            // TODO Set __gc for userdata metatables
            lua_setmetatable(L, -2);
        }

        inline static T& to(lua_State* L, int index = -1) {

            void* ptr = lua_touserdata(L, index);
            return *reinterpret_cast<T*>(ptr);
        }

        inline static bool is(lua_State* L, int index = -1) {

            return luaL_testudata(L, index, utils::demangle<T>().c_str()) != nullptr;
        }
    };

    template<typename T>
    inline void push(lua_State* L, const T& value) {TypeAdapter<T>::push(L, value);}

    template<typename T>
    inline bool is(lua_State* L, int index = -1) {return TypeAdapter<T>::is(L, index);}

    template<typename T>
    inline T to(lua_State* L, int index = -1) {return TypeAdapter<T>::to(L, index);}

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

    template<typename T>
    struct TypeAdapter<std::optional<T>> {
        static bool is  (lua_State* L, int index = -1) {
            return lua_isnil(L, index) || lua::is<T>(L, index);
        }
        static std::optional<T> to (lua_State* L, int index = -1) {
            return lua_isnil(L, index) ? std::nullopt : lua::to<T>(L, index);
        }
        static void push(lua_State* L, const std::optional<T>& value) {
            if (value)
                lua::push(L, *value);
            else
                lua_pushnil(L);
        }
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
