//
// Created by Maksym Maisak on 3/1/19.
//

#ifndef SAXION_Y2Q2_RENDERING_LUACLOSURE_H
#define SAXION_Y2Q2_RENDERING_LUACLOSURE_H

#include "LuaState.h"
#include "LuaStack.h"
#include <type_traits>
#include <functional>

namespace lua {

    // T without const, volatile, & or &&
    // unqualified_t<const std::string&> is std::string
    // Equivalent to std::remove_cvref_t from C++20
    template<typename T>
    using unqualified_t = std::remove_cv_t<std::remove_reference_t<T>>;

    template<typename TResult, typename TOwner, typename... TArgs>
    using memberFunctionPtr = TResult(TOwner::*)(TArgs...);

    template<typename TResult, typename... TArgs>
    using functionPtr = TResult(*)(TArgs...);

    class ClosureHelper {

    public:

        /// Pushes a C closure out of a given member function pointer onto the lua stack.
        /// Handles getting the arguments out of the lua stack and pushing the result onto it.
        template<typename TResult, typename TOwner, typename... TArgs>
        static inline void makeClosure(en::LuaState& lua, memberFunctionPtr<TResult, TOwner, TArgs...> memberFunction, TOwner* typeInstance);

        /// Pushes a C closure out of a given function pointer onto the lua stack.
        /// Handles getting the arguments out of the lua stack and pushing the result onto it.
        template<typename TResult, typename... TArgs>
        static inline void makeClosure(en::LuaState& lua, functionPtr<TResult, TArgs...> freeFunction);

    private:

        template<typename TResult, typename TOwner, typename... TArgs>
        static inline int callMember(lua_State* l);

        template<typename TResult, typename... TArgs>
        static inline int call(lua_State* l);

        template<typename... TArgs>
        static inline std::tuple<TArgs...> readArgsFromStack(lua_State* l);

        template<typename TResult>
        static inline void pushResult(lua_State* l, const TResult& result);
    };

    template<typename TResult, typename TOwner, typename... TArgs>
    void ClosureHelper::makeClosure(en::LuaState& lua, memberFunctionPtr<TResult, TOwner, TArgs...> memberFunction, TOwner* typeInstance) {

        // Put the member function pointer into a full userdata instead of a light userdata
        // because member function pointers for some types may be bigger than a void*.
        lua::TypeAdapter<decltype(memberFunction)>::push(lua, memberFunction);
        lua_pushlightuserdata(lua, typeInstance);
        lua_pushcclosure(lua, &callMember<TResult, TOwner, unqualified_t<TArgs>...>, 2);
    }

    template<typename TResult, typename... TArgs>
    void ClosureHelper::makeClosure(en::LuaState& lua, functionPtr<TResult, TArgs...> freeFunction) {

        lua_pushlightuserdata(lua, (void*)freeFunction);
        lua_pushcclosure(lua, &call<TResult, unqualified_t<TArgs>...>, 1);
    }

    template<typename TResult, typename TOwner, typename... TArgs>
    int ClosureHelper::callMember(lua_State* l) {

        void* userdataVoidPtr = lua_touserdata(l, lua_upvalueindex(1));
        auto memberFunction = *static_cast<memberFunctionPtr<TResult, TOwner, TArgs...>*>(userdataVoidPtr);

        auto* owner = (TOwner*)lua_touserdata(l, lua_upvalueindex(2));

        std::tuple<TArgs...> arguments = readArgsFromStack<TArgs...>(l);

        if constexpr (std::is_void_v<TResult>) {

            (*owner.*memberFunction)(std::get<TArgs>(arguments)...);
            return 0;

        } else {

            pushResult(l, (*owner.*memberFunction)(std::get<TArgs>(arguments)...));
            return 1;
        }
    }

    template<typename TResult, typename... TArgs>
    int ClosureHelper::call(lua_State* l) {

        auto* function = (functionPtr<TResult, TArgs...>)lua_touserdata(l, lua_upvalueindex(1));

        std::tuple<TArgs...> arguments = readArgsFromStack<TArgs...>(l);

        if constexpr (std::is_void_v<TResult>) {

            (*function)(std::get<TArgs>(arguments)...);
            return 0;

        } else {

            pushResult(l, (*function)(std::get<TArgs>(arguments)...));
            return 1;
        }
    }

    /// Reads the arguments from the stack.
    /// Brace initialization {} argument evaluation order is guaranteed left to right.
    /// Function call argument evaluation order is unspecified, so we can't just call a function with this pack expansion,
    /// that might cause the i++ being evaluated in the wrong order, i.e. getting the arguments from the wrong indices.
    /// So we put the arguments in a tuple first before calling the function.
    template<typename... TArgs>
    std::tuple<TArgs...> ClosureHelper::readArgsFromStack(lua_State* l) {
        int i = 1;
        return {lua::TypeAdapter<TArgs>::to(l, i++)...};
    }

    template<typename TResult>
    void ClosureHelper::pushResult(lua_State* l, const TResult& result) {
        lua::TypeAdapter<unqualified_t<TResult>>::push(l, result);
    }
}

#endif //SAXION_Y2Q2_RENDERING_LUACLOSURE_H
