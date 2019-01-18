//
// Created by Maksym Maisak on 31/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_COMPONENTSTOLUA_H
#define SAXION_Y2Q2_RENDERING_COMPONENTSTOLUA_H

#include <map>
#include <type_traits>
#include <cassert>
#include "engine/core/lua/LuaState.h"
#include "MetatableHelper.h"
#include "Actor.h"

// Calls en::ComponentsToLua::registerType<T>(#T); at dynamic initialization
// Put this in a class definition
#define LUA_TYPE(T) inline static const auto __componentTypeRequirement = en::LuaTypeRequirement<T>(#T);

#define LUA_REGISTER_TYPE(T) en::ComponentsToLua::registerType<T>(#T);

namespace en {

    using LuaComponentFactoryFunction = std::function<void(Actor&, LuaState&)>;
    using InitializeMetatableFunction = std::function<void(LuaState&)>;

    namespace detail {

        template<typename T, typename = void>
        struct LuaComponentFactoryFunctionOf {

            inline static void addComponent(Actor& actor, LuaState&) {actor.add<T>();}
            inline static LuaComponentFactoryFunction get() {return addComponent;}
        };

        template<typename T>
        struct LuaComponentFactoryFunctionOf<T, std::enable_if_t<std::is_convertible_v<decltype(&T::addFromLua), LuaComponentFactoryFunction>>> {

            inline static LuaComponentFactoryFunction get() {return T::addFromLua;}
        };

        template<typename T, typename = void>
        struct InitializeMetatableFunctionOf {

            inline static void initializeMetatable(LuaState&) {}
            inline static InitializeMetatableFunction get() {return initializeMetatable;}
        };

        template<typename T>
        struct InitializeMetatableFunctionOf<T, std::enable_if_t<std::is_convertible_v<decltype(&std::remove_pointer_t<utils::unqualified_t<T>>::initializeMetatable), InitializeMetatableFunction>>> {

            inline static void initializeMetatable(LuaState& lua) {

                using TComponent = std::remove_pointer_t<utils::unqualified_t<T>>;

                getMetatable<T>(lua);
                TComponent::initializeMetatable(lua);
                lua_pop(lua, 1);
            }

            inline static InitializeMetatableFunction get() {return initializeMetatable;}
        };
    }

    /// Handles reading component definitions out of lua values.
    /// See makeComponent
    /// Use registerComponentType<T>(name) to map a type name to a component type
    class ComponentsToLua {

    public:

        template<typename TComponent>
        static void registerType(const std::string& name);

        /// Adds a component of a given type from a value at the given index in the lua stack
        static void makeComponent(Actor& actor, const std::string& componentTypeName, int componentValueIndex = -1);

        /// Populates metatables of registered types by calling their initializeMetatable function with the metatable being on top of the stack.
        static void populateMetatables(LuaState& lua);

        static void printDebugInfo();

    private:

        struct TypeInfo {

            LuaComponentFactoryFunction addFromLua;
            InitializeMetatableFunction initializeMetatable;
        };

        // Doing it this way instead of just having a static field makes sure the map is initialized whenever it's needed.
        inline static std::map<std::string, TypeInfo>& getNameToTypeInfoMap() {
            static std::map<std::string, TypeInfo> nameToTypeInfoMap;
            return nameToTypeInfoMap;
        }
    };

    template<typename TComponent>
    class LuaTypeRequirement {

    public:

        explicit inline LuaTypeRequirement(const std::string& name) {

            if (isRegistered) return;

            ComponentsToLua::registerType<TComponent>(name);
            ComponentsToLua::registerType<TComponent*>(name + " *");

            isRegistered = true;
        }

    private:

        inline static bool isRegistered = false;
    };

    template<typename T>
    inline void ComponentsToLua::registerType(const std::string& name) {

        LuaComponentFactoryFunction addFromLua          = detail::LuaComponentFactoryFunctionOf<T>::get();
        InitializeMetatableFunction initializeMetatable = detail::InitializeMetatableFunctionOf<T>::get();

        auto& map = getNameToTypeInfoMap();
        auto it = map.find(name);
        if (it != map.end()) {
            std::cout << "Warning: type " << name << " already registered" << std::endl;
            return;
        }

        getNameToTypeInfoMap().emplace(name, TypeInfo{addFromLua, initializeMetatable});
    }
}

#endif //SAXION_Y2Q2_RENDERING_COMPONENTSTOLUA_H
