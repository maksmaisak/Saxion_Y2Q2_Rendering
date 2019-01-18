//
// Created by Maksym Maisak on 21/10/18.
//

#include "Actor.h"
#include "Engine.h"
#include "Transform.h"
#include "Name.h"

namespace en {

    Actor::Actor(Engine& engine, Entity entity) :
        m_engine(&engine),
        m_registry(&engine.getRegistry()),
        m_entity(entity) {}


    void Actor::initializeMetatable(LuaState& lua) {

        lua.setField("isValid", &Actor::operator bool);

        lua.setField("getTransform", [](Actor& actor){
            auto* ptr = actor.tryGet<Transform>();
            return ptr ? std::make_optional(ptr) : std::nullopt;
        });

        lua.setField("getName", [](Actor& actor){
            Name* ptr = actor.tryGet<Name>();
            return ptr ? std::make_optional(ptr->value) : std::nullopt;
        });
    }
}