//
// Created by Maksym Maisak on 2019-01-19.
//

#include "Light.h"

using namespace en;

void Light::addFromLua(Actor& actor, LuaState& lua) {

    //luaL_checktype(lua, -1, LUA_TTABLE);
    auto& light = actor.add<Light>();
}

void Light::initializeMetatable(LuaState& lua) {

}
