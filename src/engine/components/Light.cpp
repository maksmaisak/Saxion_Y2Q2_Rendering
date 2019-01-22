//
// Created by Maksym Maisak on 2019-01-19.
//

#include "Light.h"
#include <map>
#include <string>
#include <algorithm>

using namespace en;

void setKind(Light& light, const std::optional<std::string>& kindName) {

    if (!kindName) return;

    static const std::map<std::string, Light::Kind> kinds = {
        {"DIRECTIONAL", Light::Kind::DIRECTIONAL},
        {"POINT", Light::Kind::POINT},
        {"SPOT", Light::Kind::SPOT}
    };

    std::string name = *kindName;
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);

    auto it = kinds.find(name);
    if (it != kinds.end()) {
        light.kind = it->second;
    }
}

void Light::addFromLua(Actor& actor, LuaState& lua) {

    auto& light = actor.add<Light>();

    luaL_checktype(lua, -1, LUA_TTABLE);

    setKind(light, lua.tryGetField<std::string>("kind"));
    light.intensity    = lua.tryGetField<float>("intensity").value_or(light.intensity);
    light.color        = lua.tryGetField<glm::vec3>("color").value_or(light.color);
    light.colorAmbient = lua.tryGetField<glm::vec3>("colorAmbient").value_or(light.colorAmbient);
}

void Light::initializeMetatable(LuaState& lua) {

    lua::addProperty(lua, "intensity"   , Property<float, Light*>(&Light::intensity));
    lua::addProperty(lua, "color"       , Property<glm::vec3, Light*>(&Light::color));
    lua::addProperty(lua, "colorAmbient", Property<glm::vec3, Light*>(&Light::colorAmbient));
}