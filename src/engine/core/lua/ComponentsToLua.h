//
// Created by Maksym Maisak on 31/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_COMPONENTSTOLUA_H
#define SAXION_Y2Q2_RENDERING_COMPONENTSTOLUA_H

#include <map>
#include <type_traits>
#include <cassert>
#include "engine/core/lua/LuaState.h"
#include "engine/actor/Actor.h"

// Calls en::ComponentsToLua::registerComponentType<T>(#T); at dynamic initialization
// Put this in a class definition
#define LUA_COMPONENT_TYPE(T) inline static const auto __componentTypeRequirement = en::ComponentTypeRequirement<T>(#T);

#define LUA_REGISTER_COMPONENT_TYPE(T) en::ComponentsToLua::registerComponentType<T>(#T);

namespace en {

    class ComponentsToLua {

        using componentFactoryFunction = std::function<void(Actor&, LuaState&)>;

    public:

        template<typename TComponent>
        static void registerComponentType(const std::string& name);

        /// Adds a component of a given type from a value at the given index in the lua stack
        static void makeComponent(en::Actor& actor, const std::string& componentTypeName, int componentValueIndex = -1);

        static void printDebugInfo();

    private:

        // Doing it this way instead of just having a static field makes sure the map is initialized whenever it's needed.
        inline static std::map<std::string, componentFactoryFunction>& getNameToMakeFunctionMap() {
            static std::map<std::string, componentFactoryFunction> nameToMakeFunctionMap;
            return nameToMakeFunctionMap;
        }

        // If no custom `addFromLua(Actor&, LuaState&)` function provided, just add the component when needed.
        template<typename TComponent, typename = void>
        struct Registerer {

            inline static void registerComponentType(const std::string& name) {
                static auto make = [](Actor& actor, LuaState& luaState){return actor.add<TComponent>();};
                getNameToMakeFunctionMap().emplace(name, make);
            }
        };

        // If a custom `addFromLua(Actor&, LuaState&)` function exists, use it.
        template<typename TComponent>
        struct Registerer<TComponent, std::enable_if_t<std::is_convertible_v<decltype(&TComponent::addFromLua), componentFactoryFunction>>> {

            inline static void registerComponentType(const std::string& name) {
                getNameToMakeFunctionMap().emplace(name, TComponent::addFromLua);
            }
        };
    };

    template<typename TComponent>
    struct ComponentTypeRequirement {

        explicit ComponentTypeRequirement(const std::string& name) {
            if (isRegistered) return;
            ComponentsToLua::registerComponentType<TComponent>(name);
            isRegistered = true;
        }

        inline static bool isRegistered = false;
    };

    template<typename TComponent>
    inline void ComponentsToLua::registerComponentType(const std::string& name) {
        ComponentsToLua::Registerer<TComponent>::registerComponentType(name);
    }
}

#endif //SAXION_Y2Q2_RENDERING_COMPONENTSTOLUA_H
