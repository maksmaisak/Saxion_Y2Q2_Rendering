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

        template<typename... TArgs>
        struct metatableSetter;/* {

            inline void set(lua_State* l, TArgs&& ... args) {

                std::cerr << "invalid arguments to setMetatable!" << std::endl;
            }
        };*/

        template<>
        struct metatableSetter<> {

            inline void set(lua_State* l) {}
        };

        template<typename TResult, typename... TArgs, typename... Rest>
        struct metatableSetter<const std::string&, functionPtr<TResult, TArgs...>, Rest...> {

            inline void set(lua_State* l, const std::string& name, functionPtr<TResult, TArgs...> freeFunction, Rest&&... rest) {

                ClosureHelper::makeClosure(l, freeFunction);
                lua_setfield(l, -2, name.c_str());

                metatableSetter<Rest...>::set(l, std::forward<Rest>(rest)...);
            }
        };

        template<typename TResult, typename TOwner, typename... TArgs, typename... Rest>
        struct metatableSetter<const std::string&, memberFunctionPtr<TResult, TOwner, TArgs...>, Rest...> {

            inline void set(lua_State* l, const std::string& name, memberFunctionPtr<TResult, TOwner, TArgs...> memberFunction, Rest&&... rest) {

                ClosureHelper::makeClosure(l, memberFunction);
                lua_setfield(l, -2, name.c_str());

                metatableSetter<Rest...>::set(l, std::forward<Rest>(rest)...);
            }
        };
    }

    template<typename T, typename... TArgs>
    inline void makeMetatable(lua_State* l, TArgs&&... args) {

        luaL_newmetatable(l, utils::demangle<T>().c_str());
        detail::metatableSetter<TArgs...>::set(l, std::forward<TArgs>(args)...);
        lua_pop(l, 1);
    }

    // Gets or adds a metatable for a given type.
    // Returns true if the metatable did not exist before.
    template<typename T>
    inline bool getMetatable(lua_State* l) {

        if (!luaL_newmetatable(l, utils::demangle<T>().c_str()))
            return false;

        lua_pushvalue(l, -1);
        lua_setfield(l, -2, "__index");
        return true;
    }
}

#endif //SAXION_Y2Q2_RENDERING_METATABLE_HELPER_H
