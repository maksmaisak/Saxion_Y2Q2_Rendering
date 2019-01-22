//
// Created by Maksym Maisak on 2019-01-22.
//

#include "Rigidbody.h"

using namespace en;

void Rigidbody::initializeMetatable(LuaState& lua) {

    lua::addProperty(lua, "velocity", Property<glm::vec3, Rigidbody*>(&Rigidbody::velocity));
    lua::addProperty(lua, "isKinematic", Property<bool, Rigidbody*>(&Rigidbody::isKinematic));
    lua::addProperty(lua, "useGravity", Property<bool, Rigidbody*>(&Rigidbody::useGravity));
    lua::addProperty(lua, "bounciness", Property<float, Rigidbody*>(&Rigidbody::bounciness));
    lua::addProperty(lua, "radius", Property<float, Rigidbody*>(&Rigidbody::radius));
}
