//
// Created by Maksym Maisak on 31/12/18.
//

#include "ComponentsToLua.h"
#include <cassert>
#include <iostream>

using namespace en;

void ComponentsToLua::makeComponent(Actor& actor, const std::string& componentTypeName, int componentValueIndex) {

    auto& lua = actor.getEngine().getLuaState();
    auto popComponentValue = lua::PopperOnDestruct(lua);
    lua_pushvalue(lua, componentValueIndex);

    auto& map = getNameToTypeInfoMap();
    auto it = map.find(componentTypeName);
    if (it == map.end()) {
        std::cout << "Unknown component type: " << componentTypeName << std::endl;
        return;
    }

    int oldTop = lua_gettop(lua);
    it->second.addFromLua(actor, lua);
    assert(oldTop == lua_gettop(lua));
}

void ComponentsToLua::populateMetatables(LuaState& lua) {

    for (auto& kvp : getNameToTypeInfoMap()) {
        kvp.second.initializeMetatable(lua);
    }
}

void ComponentsToLua::printDebugInfo() {

    std::cout << std::endl << "Registered component types:" << std::endl;

    for (auto& pair : getNameToTypeInfoMap()) {
        std::cout << pair.first << std::endl;
    }

    std::cout << std::endl;
}