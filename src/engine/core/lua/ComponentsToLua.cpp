//
// Created by Maksym Maisak on 31/12/18.
//

#include "ComponentsToLua.h"
#include <cassert>

using namespace en;

void ComponentsToLua::makeComponent(Actor& actor, const std::string& componentTypeName, int componentValueIndex) {

    auto& lua = actor.getEngine().getLuaState();
    auto popComponentValue = lua::PopperOnDestruct(lua);
    lua_pushvalue(lua, componentValueIndex);

    auto it = m_nameToMakeFunction.find(componentTypeName);
    if (it == m_nameToMakeFunction.end()) {
        std::cout << "Unknown component type: " << componentTypeName << std::endl;
        return;
    }

    int oldTop = lua_gettop(lua);
    it->second(actor, lua);
    assert(oldTop == lua_gettop(lua));
}