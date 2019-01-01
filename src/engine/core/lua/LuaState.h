//
// Created by Maksym Maisak on 29/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_LUASTATE_H
#define SAXION_Y2Q2_RENDERING_LUASTATE_H

#include <lua/lua.hpp>
#include <memory>
#include <cassert>
#include <string>
#include <optional>

#include "LuaStack.h"

namespace en {

    using namespace lua;

    class LuaState final {

    public:

        LuaState();

        bool pCall(int numArgs = 0, int numResults = 0, int messageHandlerIndex = 0);
        bool loadFile(const std::string& filename);
        bool doFile(const std::string& filename);

        /// Creates a new environment table that inherits from the global one.
        /// Pushes it onto the stack.
        void makeEnvironment();

        /// Sets the environment of the closure on top of the stack to the value
        /// at the given index.
        void setEnvironment(int environmentIndex);

        /// Loads a file and runs it in a new environment (see makeEnvironment)
        /// Pushes the environment table onto the stack.
        bool doFileInNewEnvironment(const std::string& filename);

        inline operator lua_State* () {return L;}

        /* TODO Implement lua::pushAdapter
        template<typename TResult, typename... TArgs>
        std::optional<TResult> protectedCall(TArgs&&... args) {

            (lua::pushAdapter<TArgs>{}(args), ...);
            lua_pcall(L, sizeof...(TArgs), 1, 0);
            return get<TResult>();
            //(lua::toAdapter<TResults>{}(L, index), ...);
        }*/

        template<typename T>
        inline std::optional<T> getGlobal(const std::string& name) {

            lua_getglobal(L, name.c_str());
            return get<T>();
        }

        template<typename T>
        inline std::optional<T> getField(const std::string& name, int tableIndex = -1) {

            if (!lua_istable(L, tableIndex)) return std::nullopt;

            tableIndex = lua_absindex(L, tableIndex);

            lua_pushstring(L, name.c_str());
            lua_gettable(L, tableIndex);
            return get<T>();
        }

        /// Pops and returns the value on top of the stack.
        template<typename T>
        inline std::optional<T> get() {

            auto popper = PopperOnDestruct(L); // pop when the function returns

            if (lua_isnil(L, -1) || !is<T>()) return std::nullopt;
            return to<T>();
        }

        template<typename T>
        inline bool is(int index = -1) const {return lua::typeAdapter<T>::is(L, index);}

        template<typename T>
        inline T    to(int index = -1) const {return lua::typeAdapter<T>::to(L, index);}

    private:

        struct LuaStateDeleter {
            inline void operator()(lua_State* L) { lua_close(L); }
        };

        void printError();

        std::unique_ptr<lua_State, LuaStateDeleter> luaStateOwner;
        lua_State* L;
    };
}

#endif //SAXION_Y2Q2_RENDERING_LUASTATE_H
