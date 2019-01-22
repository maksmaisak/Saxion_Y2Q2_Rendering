//
// Created by Maksym Maisak on 3/1/19.
//

#ifndef SAXION_Y2Q2_RENDERING_LUACLOSURE_H
#define SAXION_Y2Q2_RENDERING_LUACLOSURE_H

#include "LuaStack.h"
#include <type_traits>
#include <functional>

#include "Demangle.h"
#include "Meta.h"

namespace lua {

    template<typename TResult, typename TOwner, typename... TArgs>
    using memberFunctionPtr = TResult(TOwner::*)(TArgs...);

    template<typename TResult, typename... TArgs>
    using functionPtr = TResult(*)(TArgs...);

    /// TODO This needs refactoring.
    /// Handling functions expecting pointers versus references,
    /// same handling for both function pointers and lambdas.
    class ClosureHelper {

    public:

        /// Pushes a C closure out of a given std::function
        /// Handles getting the arguments out of the lua stack and pushing the result onto it.
        template<typename F>
        static inline void makeClosure(lua_State* l, const F& function);

        template<typename TResult, typename... TArgs>
        static inline void makeClosure(lua_State* l, const std::function<TResult(TArgs...)>& function);

            /// Pushes a C closure out of a given function pointer onto the lua stack.
        /// Handles getting the arguments out of the lua stack and pushing the result onto it.
        template<typename TResult, typename... TArgs>
        static inline void makeClosure(lua_State* l, functionPtr<TResult, TArgs...> freeFunction);

        /// Pushes a C closure out of a given member function pointer onto the lua stack.
        /// Handles getting the arguments out of the lua stack and pushing the result onto it.
        template<typename TResult, typename TOwner, typename... TArgs>
        static inline void makeClosure(lua_State* l, memberFunctionPtr<TResult, TOwner, TArgs...> memberFunction, TOwner* typeInstance);

        /// Pushes a C closure out of a given member function pointer onto the lua stack, while getting the *this pointer from the stack.
        /// Handles getting the arguments out of the lua stack and pushing the result onto it.
        template<typename TResult, typename TOwner, typename... TArgs>
        static inline void makeClosure(lua_State* l, memberFunctionPtr<TResult, TOwner, TArgs...> memberFunction);

        template<typename TResult, typename TOwner, typename... TArgs>
        static inline void makeClosure(lua_State* l, TResult(TOwner::*memberFunctionConst)(TArgs...) const) {
            makeClosure(l, reinterpret_cast<memberFunctionPtr<TResult, TOwner, TArgs...>>(memberFunctionConst));
        }

        template<typename TResult, typename TOwner, typename... TArgs>
        static inline void makeClosure(lua_State* l, memberFunctionPtr<TResult, TOwner, TArgs...> const memberFunctionConst, const TOwner* typeInstanceConst) {
            makeClosure(l, reinterpret_cast<memberFunctionPtr<TResult, TOwner, TArgs...>>(memberFunctionConst), reinterpret_cast<TOwner*>(typeInstanceConst));
        }

    private:

        template<typename TResult, typename... TArgs>
        static inline int call(lua_State* l);

        template<typename TResult, typename TOwner, typename... TArgs>
        static inline int callMember(lua_State* l);

        template<typename TResult, typename TOwner, typename... TArgs>
        static inline int callMemberFromStack(lua_State* l);

        template<typename TResult, typename... TArgs>
        static inline int callStdFunction(lua_State* l);

        template<typename... TArgs>
        static inline std::tuple<TArgs...> readArgsFromStack(lua_State* l, int startIndex = 1);

        template<typename TResult>
        static inline void pushResult(lua_State* l, const TResult& result);
    };

    template<typename F>
    void ClosureHelper::makeClosure(lua_State* l, const F& func) {

        using traits = utils::functionTraits<decltype(&utils::remove_cvref_t<F>::operator())>;
        static_assert(traits::isFunction);
        std::function<typename traits::Signature> function = func;
        makeClosure(l, function);
    }

    template<typename TResult, typename... TArgs>
    void ClosureHelper::makeClosure(lua_State* l, const std::function<TResult(TArgs...)>& function) {

        lua::push(l, function);
        lua_pushcclosure(l, &callStdFunction<TResult, utils::remove_cvref_t<TArgs>...>, 1);
    }

    template<typename TResult, typename... TArgs>
    void ClosureHelper::makeClosure(lua_State* l, functionPtr<TResult, TArgs...> freeFunction) {

        lua_pushlightuserdata(l, (void*)freeFunction);
        lua_pushcclosure(l, &call<TResult, utils::remove_cvref_t<TArgs>...>, 1);
    }

    template<typename TResult, typename TOwner, typename... TArgs>
    void ClosureHelper::makeClosure(lua_State* l, memberFunctionPtr<TResult, TOwner, TArgs...> memberFunction, TOwner* typeInstance) {

        // Put the member function pointer into a full userdata instead of a light userdata
        // because member function pointers for some types may be bigger than a void*.
        lua::push(l, memberFunction);
        lua_pushlightuserdata(l, typeInstance);
        lua_pushcclosure(l, &callMember<TResult, TOwner, utils::remove_cvref_t<TArgs>...>, 2);
    }

    template<typename TResult, typename TOwner, typename... TArgs>
    void ClosureHelper::makeClosure(lua_State* l, memberFunctionPtr<TResult, TOwner, TArgs...> memberFunction) {

        lua::push(l, memberFunction);
        lua_pushcclosure(l, &callMemberFromStack<TResult, TOwner, utils::remove_cvref_t<TArgs>...>, 1);
    }

    template<typename TResult, typename... TArgs>
    int ClosureHelper::callStdFunction(lua_State* l) {

        void* voidPtr = lua_touserdata(l, lua_upvalueindex(1));
        auto& function = *static_cast<std::function<TResult(TArgs...)>*>(voidPtr);

        std::tuple<TArgs...> arguments = readArgsFromStack<TArgs...>(l);

        if constexpr (std::is_void_v<TResult>) {

            std::apply(function, arguments);
            return 0;

        } else {

            pushResult(l, std::apply(function, arguments));
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

    template<typename TResult, typename TOwner, typename... TArgs>
    int ClosureHelper::callMemberFromStack(lua_State* l) {

        void* userdataVoidPtr = lua_touserdata(l, lua_upvalueindex(1));
        auto memberFunction = *static_cast<memberFunctionPtr<TResult, TOwner, TArgs...>*>(userdataVoidPtr);

        TOwner* owner = nullptr;
        if (lua::is<TOwner*>(l, 1)) {
            owner = lua::to<TOwner*>(l, 1);
        } else {
            owner = static_cast<TOwner*>(lua_touserdata(l, 1));
        }

        std::tuple<TArgs...> arguments = readArgsFromStack<TArgs...>(l, 2);

        if constexpr (std::is_void_v<TResult>) {

            std::apply([=](auto&&... args){(*owner.*memberFunction)(args...);}, arguments);
            return 0;

        } else {

            pushResult(l, std::apply([=](auto&&... args){return (*owner.*memberFunction)(args...);}, arguments));
            return 1;
        }
    }

    template<typename T>
    inline bool checkArgType(lua_State* l, int index) {

        if (lua::is<T>(l, index))
            return true;

        //std::cerr << "Invalid argument #" + std::to_string(index) + ": expected " + utils::demangle<T>() << std::endl;
        luaL_error(l, "Invalid argument #%d: expected %s", index, utils::demangle<T>().c_str());
        return false;
    }

    /// Reads the arguments from the stack.
    /// Brace initialization {} argument evaluation order is guaranteed left to right.
    /// Function call argument evaluation order is unspecified, so we can't just call a function with this pack expansion,
    /// that might cause the i++ being evaluated in the wrong order, i.e. getting the arguments from the wrong indices.
    /// So we put the arguments in a tuple first before calling the function.
    template<typename... TArgs>
    std::tuple<TArgs...> ClosureHelper::readArgsFromStack(lua_State* l, int startIndex) {

        {
            int i = startIndex;
            (checkArgType<TArgs>(l, i++), ...);
        }

        int i = startIndex;
        return {lua::to<TArgs>(l, i++)...};
    }

    template<typename TResult>
    void ClosureHelper::pushResult(lua_State* l, const TResult& result) {
        lua::TypeAdapter<utils::remove_cvref_t<TResult>>::push(l, result);
    }
}

#endif //SAXION_Y2Q2_RENDERING_LUACLOSURE_H
