//
// Created by Maksym Maisak on 2019-01-22.
//

#include "Rigidbody.h"

using namespace en;

void Rigidbody::initializeMetatable(LuaState& lua) {

    lua::addProperty(lua, "velocity",    property(&Rigidbody::velocity));
    lua::addProperty(lua, "isKinematic", property(&Rigidbody::isKinematic));
    lua::addProperty(lua, "useGravity",  property(&Rigidbody::useGravity));
    lua::addProperty(lua, "bounciness",  property(&Rigidbody::bounciness));
    lua::addProperty(lua, "radius",      property(&Rigidbody::radius));
}
