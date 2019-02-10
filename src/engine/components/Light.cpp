//
// Created by Maksym Maisak on 2019-01-19.
//

#include "Light.h"
#include <map>
#include <string>
#include <algorithm>
#include <GL/glew.h>
#include "ComponentReference.h"
#include "Transform.h"
#include "GLHelpers.h"

using namespace en;

Light::Kind readKind(LuaState& lua) {

    std::optional<std::string> kindName = lua.tryGetField<std::string>("kind");

    if (!kindName)
        return Light::Kind::POINT;

    static const std::map<std::string, Light::Kind> kinds = {
        {"DIRECTIONAL", Light::Kind::DIRECTIONAL},
        {"POINT", Light::Kind::POINT},
        {"SPOT", Light::Kind::SPOT}
    };

    std::string name = *kindName;
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);

    auto it = kinds.find(name);
    if (it != kinds.end()) {
        return it->second;
    }

    return Light::Kind::POINT;
}

void Light::addFromLua(Actor& actor, LuaState& lua) {

    luaL_checktype(lua, -1, LUA_TTABLE);
    actor.add<Light>(readKind(lua));
}

void Light::initializeMetatable(LuaState& lua) {

    lua::addProperty(lua, "intensity", property(&Light::intensity));
    lua::addProperty(lua, "color", property(&Light::color));
    lua::addProperty(lua, "ambientColor", property(&Light::colorAmbient));
}

Light::Light(Kind kind) : kind(kind) {}