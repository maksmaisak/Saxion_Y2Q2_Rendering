//
// Created by Maksym Maisak on 29/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_LUASTATE_H
#define SAXION_Y2Q2_RENDERING_LUASTATE_H

#include <lua/lua.hpp>
#include <memory>
#include <string>
#include <optional>

#include "LuaStack.h"

namespace en {

    using namespace lua;

    class LuaState final {

    public:

        LuaState();

        int doFile(const std::string& filename);

        inline operator lua_State* () {return L;}

        template<typename T>
        inline std::optional<T> getGlobal(const std::string& name) {

            lua_getglobal(L, name.c_str());
            return get<T>();
        }

        template<typename T>
        inline std::optional<T> get() {

            auto popper = PopperOnDestruct(L); // pop when the function returns
            if (lua_isnil(L, -1)) return std::nullopt;
            return to<T>();
        }

        template<typename T>
        inline T to() {return lua::toAdapter<T>{}(L);}

    private:

        struct LuaStateDeleter {
            inline void operator()(lua_State* L) { lua_close(L); }
        };

        std::unique_ptr<lua_State, LuaStateDeleter> luaStateOwner;
        lua_State* L;
    };
}

#endif //SAXION_Y2Q2_RENDERING_LUASTATE_H
