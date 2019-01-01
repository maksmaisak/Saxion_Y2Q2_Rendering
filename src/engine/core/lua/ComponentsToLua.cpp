//
// Created by Maksym Maisak on 31/12/18.
//

#include "ComponentsToLua.h"

using namespace en;

void ComponentsToLua::makeComponent(Actor& actor, const std::string& componentTypeName, int componentValueIndex) {

    auto& lua = actor.getEngine().getLuaState();
    auto popComponentValue = lua::PopperOnDestruct(lua);
    lua_pushvalue(lua, componentValueIndex);

    auto it = m_nameToMakeFunction.find(componentTypeName);
    if (it == m_nameToMakeFunction.end())
        throw "Unknown component type: " + componentTypeName;

    it->second(actor, lua);
}