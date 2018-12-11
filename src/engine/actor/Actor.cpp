//
// Created by Maksym Maisak on 21/10/18.
//

#include "Actor.h"
#include "Engine.h"

namespace en {

    Actor::Actor(Engine& engine, Entity entity) :
        m_engine(&engine),
        m_registry(&engine.getRegistry()),
        m_entity(entity) {}
}