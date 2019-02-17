//
// Created by Maksym Maisak on 21/10/18.
//

#include "Actor.h"
#include "Engine.h"
#include "Transform.h"
#include "Name.h"
#include "LuaState.h"
#include "Destroy.h"

namespace en {

    Actor::Actor(Engine& engine, Entity entity) :
        m_engine(&engine),
        m_registry(&engine.getRegistry()),
        m_entity(entity)
        {}

    std::string Actor::getName() const {

        Name* ptr = tryGet<Name>();
        if (ptr) return ptr->value;
        return "unnamed";
    }

    void Actor::destroy() {

        m_registry->destroy(m_entity);
    }

    int pushByTypeName(lua_State* L) {

        auto actor = lua::check<Actor>(L, 1);
        if (!actor)
            return 0;

        auto name = lua::check<std::string>(L, 2);
        ComponentsToLua::pushComponentReferenceByTypeName(L, actor, name);

        return 1;
    }

    int addByTypeName(lua_State* L) {

        auto& actor = lua::check<Actor>(L, 1);
        if (!actor)
            return 0;

        auto name = lua::check<std::string>(L, 2);
        if (lua_isnoneornil(L, 3))
            ComponentsToLua::addComponentByTypeName(L, actor, name);
        else
            ComponentsToLua::addComponentByTypeName(L, actor, name, 3);

        return 1;
    }

    int removeByTypeName(lua_State* L) {

        auto& actor = lua::check<Actor>(L, 1);
        if (!actor)
            return 0;

        auto name = lua::check<std::string>(L, 2);
        ComponentsToLua::removeComponentByTypeName(L, actor, name);

        return 0;
    }

    void Actor::initializeMetatable(LuaState& lua) {

        lua.setField("get", &pushByTypeName);
        lua.setField("add", &addByTypeName);
        lua.setField("remove", &removeByTypeName);
        lua.setField("destroyImmediate", &Actor::destroy);
        lua.setField("destroy", [](Actor& actor){
            if (actor && !actor.tryGet<Destroy>())
                actor.add<Destroy>();
        });

        lua::addProperty(lua, "name", lua::property(
            [](Actor& actor){
                Name* ptr = actor.tryGet<Name>();
                return ptr ? std::make_optional(ptr->value) : std::nullopt;
            },
            [](Actor& actor, const std::string& newName) {
                Name* nameComponent = actor.tryGet<Name>();
                if (nameComponent) {
                    nameComponent->value = newName;
                } else {
                    actor.add<Name>(newName);
                }
            }
        ));

        lua::addProperty(lua, "isValid", lua::readonlyProperty([](Actor& actor) -> bool {
            return actor;
        }));

        lua::addProperty(lua, "isDestroyed", lua::readonlyProperty([](Actor& actor) -> bool {
            return !actor || actor.tryGet<Destroy>();
        }));
    }
}