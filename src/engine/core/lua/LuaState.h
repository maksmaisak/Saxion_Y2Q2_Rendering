//
// Created by Maksym Maisak on 29/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_LUASTATE_H
#define SAXION_Y2Q2_RENDERING_LUASTATE_H

#include <lua.hpp>
#include <memory>
#include <cassert>
#include <string>
#include <optional>

#include "LuaStack.h"
#include "ClosureHelper.h"

namespace en {

    using namespace lua;

    /// A wrapper around a lua_State*. Can be implicitly cast to that.
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

        /*
        template<typename TResult, typename... TArgs>
        std::optional<TResult> protectedCall(TArgs&&... args) {

            (lua::push<TArgs>{}(args), ...);
            lua_pcall(L, sizeof...(TArgs), 1, 0);
            return get<TResult>();
            //(lua::to<TResults>(L, index), ...);
        }*/

        template<typename T>
        inline std::optional<T> getGlobal(const std::string& name) {

            lua_getglobal(L, name.c_str());
            return get<T>();
        }

        template<typename T>
        inline std::optional<T> getField(const std::string& name, int tableIndex = -1) {

            if (!lua_istable(L, tableIndex)) return std::nullopt;

            lua_getfield(L, tableIndex, name.c_str());
            return get<T>();
        }

        template<typename T>
        inline void setField(const std::string& name, T&& value, int tableIndex = -1) {

            luaL_checktype(L, tableIndex, LUA_TTABLE);
            tableIndex = lua_absindex(L, tableIndex);

            if constexpr (utils::functionTraits<utils::unqualified_t<T>>::isFunction && !std::is_same_v<lua_CFunction, T>) {
                ClosureHelper::makeClosure(L, std::forward<T>(value));
            } else {
                lua::push(L, std::forward<T>(value));
            }

            lua_setfield(L, tableIndex, name.c_str());
        }

        template<typename TResult, typename TOwner, typename... Args>
        inline void setField(const std::string& name, TResult(TOwner::*memberFunctionPtr)(Args...), TOwner* ownerPtr, int tableIndex = -1) {

            luaL_checktype(L, tableIndex, LUA_TTABLE);
            tableIndex = lua_absindex(L, tableIndex);

            ClosureHelper::makeClosure(L, memberFunctionPtr, ownerPtr);

            lua_setfield(L, tableIndex, name.c_str());
        }

        /// Pops and returns the value on top of the stack.
        template<typename T>
        inline std::optional<T> get() {

            auto popper = PopperOnDestruct(L); // pop when the function returns

            if (lua_isnil(L, -1) || !is<T>()) return std::nullopt;
            return to<T>();
        }

        template<typename T>
        inline bool is(int index = -1) const {return lua::is<T>(L, index);}

        template<typename T>
        inline T    to(int index = -1) const {return lua::to<T>(L, index);}

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
