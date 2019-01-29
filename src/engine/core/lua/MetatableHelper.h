//
// Created by Maksym Maisak on 3/1/19.
//

#ifndef SAXION_Y2Q2_RENDERING_METATABLE_HELPER_H
#define SAXION_Y2Q2_RENDERING_METATABLE_HELPER_H

#include "LuaState.h"
#include "LuaStack.h"
#include "ClosureHelper.h"
#include "Meta.h"
#include "Demangle.h"
#include <functional>
#include <vector>

namespace lua {

    namespace detail {

        /// The __index function: (table, key) -> value
        /// Try using a property getter from __getters, otherwise look it up in the metatable
        int indexFunction(lua_State* L);

        /// The __index function: (table, key, value) -> ()
        /// Try using a property setter from __setters, otherwise just rawset it
        int newindexFunction(lua_State* L);

        using InitializeMetatableFunction = std::function<void(en::LuaState&)>;
        using InitializeEmptyMetatableFunction = std::function<void(en::LuaState&)>;

        template<typename T, typename = void>
        struct InitializeMetatableFunctionOf {

            inline static void initializeMetatable(en::LuaState&) {}
        };

        template<typename T>
        struct InitializeMetatableFunctionOf<T, std::enable_if_t<std::is_convertible_v<decltype(&std::remove_pointer_t<utils::remove_cvref_t<T>>::initializeMetatable), InitializeMetatableFunction>>> {

            inline static void initializeMetatable(en::LuaState& lua) {

                using TComponent = std::remove_pointer_t<utils::remove_cvref_t<T>>;

                int oldTop = lua_gettop(lua);
                TComponent::initializeMetatable(lua);
                int newTop = lua_gettop(lua);
                assert(oldTop == newTop);
            }
        };

        template<typename T, typename = void>
        struct InitializeEmptyMetatable {

            inline static void initializeEmptyMetatable(en::LuaState& lua) {

                lua_newtable(lua);
                lua_setfield(lua, -2, "__getters");

                lua_newtable(lua);
                lua_setfield(lua, -2, "__setters");

                lua_pushcfunction(lua, &detail::indexFunction);
                lua_setfield(lua, -2, "__index");

                lua_pushcfunction(lua, &detail::newindexFunction);
                lua_setfield(lua, -2, "__newindex");

                if constexpr (std::is_pointer_v<T>) {
                    lua.setField("__eq", [](T a, T b) { return a == b; });
                }

                // TODO Set __gc for userdata metatables

                InitializeMetatableFunctionOf<T>::initializeMetatable(lua);
            }
        };

        template<typename T>
        struct InitializeEmptyMetatable<T, std::enable_if_t<std::is_convertible_v<decltype(&std::remove_pointer_t<utils::remove_cvref_t<T>>::initializeEmptyMetatable), InitializeEmptyMetatableFunction>>> {

            inline static void initializeEmptyMetatable(en::LuaState& lua) {

                using TComponent = std::remove_pointer_t<utils::remove_cvref_t<T>>;

                int oldTop = lua_gettop(lua);
                TComponent::initializeEmptyMetatable(lua);
                int newTop = lua_gettop(lua);
                assert(oldTop == newTop);
            }
        };
    }

    // Gets or adds a metatable for a given type.
    // Returns true if the metatable did not exist before.
    template<typename T>
    inline bool getMetatable(lua_State* L) {

        auto lua = en::LuaState(L);

        if (!luaL_newmetatable(lua, utils::demangle<T>().c_str()))
            return false;

        std::cout << "Created metatable for type " << utils::demangle<T>() << std::endl;

        detail::InitializeEmptyMetatable<T>::initializeEmptyMetatable(lua);

        return true;
    }

    struct NoAccessor {};

    template<typename G, typename S>
    struct PropertyWrapper {

        using HasGetter = std::negation<std::is_void<G>>;
        using HasSetter = std::negation<std::is_void<S>>;

        using Getter = std::conditional_t<HasGetter::value, G, NoAccessor>;
        using Setter = std::conditional_t<HasSetter::value, S, NoAccessor>;

        // GetterT and SetterT are expected to be versions of Getter and Setter with various cvref modifiers.
        template<typename GetterT, typename SetterT>
        inline PropertyWrapper(GetterT&& getter, SetterT&& setter) :
            m_getter(std::forward<GetterT>(getter)),
            m_setter(std::forward<SetterT>(setter))
        {}

        inline const Getter& getGetter() const {return m_getter;}
        inline const Setter& getSetter() const {return m_setter;}

    private:
        Getter m_getter = {};
        Setter m_setter = {};
    };

    /// Adds a getter and setter, if present, to the __getter and __setter tables in the table on top of stack.
    /// That table is assumed to be a metatable.
    template<typename G, typename S>
    inline void addProperty(lua_State* L, const std::string& name, const PropertyWrapper<G, S>& property) {

        if constexpr (PropertyWrapper<G, S>::HasGetter::value) {

            auto popGetters = PopperOnDestruct(L);
            lua_getfield(L, -1, "__getters");

            ClosureHelper::makeClosure(L, property.getGetter());
            lua_setfield(L, -2, name.c_str());
        }

        if constexpr (PropertyWrapper<G, S>::HasSetter::value) {

            auto popSetters = PopperOnDestruct(L);
            lua_getfield(L, -1, "__setters");

            ClosureHelper::makeClosure(L, property.getSetter());
            lua_setfield(L, -2, name.c_str());
        }
    }

    template<typename Getter, typename Setter>
    inline auto property(Getter&& getter, Setter&& setter) {

        using getterTraits = utils::functionTraits<Getter>;
        using setterTraits = utils::functionTraits<Setter>;
        static_assert(getterTraits::isFunction);
        static_assert(setterTraits::isFunction);
        return PropertyWrapper<typename getterTraits::FunctionType, typename setterTraits::FunctionType>(getter, setter);
    }

    template<typename T, typename Owner>
    inline auto property(T Owner::* memberPtr) {

        return property(
            [memberPtr](en::ComponentReference<Owner> owner){ return *owner.*memberPtr; },
            [memberPtr](en::ComponentReference<Owner> owner, const T& value){ return *owner.*memberPtr = value; }
        );
    }

    template<typename Getter>
    inline auto readonlyProperty(Getter&& getter) {

        using traits = utils::functionTraits<Getter>;
        static_assert(traits::isFunction);
        return PropertyWrapper<typename traits::FunctionType, void>(getter, NoAccessor());
    }

    template<typename Setter>
    inline auto writeonlyProperty(Setter&& setter) {

        using traits = utils::functionTraits<Setter>;
        static_assert(traits::isFunction);
        return PropertyWrapper<void, typename traits::FunctionType>(NoAccessor(), setter);
    }
}

#endif //SAXION_Y2Q2_RENDERING_METATABLE_HELPER_H
