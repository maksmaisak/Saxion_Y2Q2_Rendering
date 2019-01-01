//
// Created by Maksym Maisak on 31/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_COMPONENTSTOLUA_H
#define SAXION_Y2Q2_RENDERING_COMPONENTSTOLUA_H

#include <map>
#include <type_traits>
#include "engine/core/lua/LuaState.h"
#include "engine/actor/Actor.h"

#define REGISTER_LUA_COMPONENT_TYPE(T) inline static struct Registerer { Registerer() {en::ComponentsToLua::registerComponentType<T>(#T);}} registerer;

namespace en {

    class ComponentsToLua {

        using componentFactoryFunction = std::function<void(Actor&, LuaState&)>;

    public:

        template<typename TComponent>
        static void registerComponentType(const std::string& name);

        static void makeComponent(en::Actor& actor, const std::string& componentTypeName, int componentValueIndex = -1);

    private:
        inline static std::map<std::string, componentFactoryFunction> m_nameToMakeFunction;

        // If no custom `addFromLua(Actor&, LuaState&)` function provided, just add the component when needed.
        template<typename TComponent, typename = void>
        struct Registerer {

            inline static void registerComponentType(const std::string& name) {
                static auto make = [](Actor& actor, LuaState& luaState){return actor.add<TComponent>();};
                m_nameToMakeFunction.emplace(name, make);
            }
        };

        // If a custom `addFromLua(Actor&, LuaState&)` function exists, use it.
        template<typename TComponent>
        struct Registerer<TComponent, std::enable_if_t<std::is_invocable_v<decltype(&TComponent::addFromLua), Actor&, LuaState&>>> {

            inline static void registerComponentType(const std::string& name) {
                m_nameToMakeFunction.emplace(name, TComponent::addFromLua);
            }
        };
    };

    template<typename TComponent>
    inline void ComponentsToLua::registerComponentType(const std::string& name) {

        std::cout << name << std::endl;
        ComponentsToLua::Registerer<TComponent>::registerComponentType(name);
    }
}

#endif //SAXION_Y2Q2_RENDERING_COMPONENTSTOLUA_H
