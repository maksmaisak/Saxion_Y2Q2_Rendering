//
// Created by Maksym Maisak on 31/12/18.
//

#include "ComponentsToLua.h"
#include <cassert>
#include <iostream>

#include "Name.h"

using namespace en;

void ComponentsToLua::printDebugInfo() {

    std::cout << std::endl << "Registered component types:" << std::endl;

    for (auto& pair : getNameToTypeInfoMap()) {
        std::cout << pair.first << std::endl;
    }

    std::cout << std::endl;
}

void ComponentsToLua::pushComponentPointerFromActorByTypeName(lua_State* L, Actor& actor, const std::string& componentTypeName) {

    auto lua = LuaState(L);

    auto& map = getNameToTypeInfoMap();
    auto it = map.find(componentTypeName);
    if (it == map.end()) {
        std::cout << "Unknown component type: " << componentTypeName << std::endl;
        lua_pushnil(L);
        return;
    }

    it->second.pushFromActor(actor, lua);
}

void ComponentsToLua::addComponentToActorByTypeName(lua_State* L, Actor& actor, const std::string& componentTypeName) {

    auto lua = LuaState(L);

    auto& map = getNameToTypeInfoMap();
    auto it = map.find(componentTypeName);
    if (it == map.end()) {
        std::cout << "Unknown component type: " << componentTypeName << std::endl;
        lua_pushnil(lua);
        return;
    }

    it->second.addToActor(actor, lua);
}

void ComponentsToLua::makeEntities(lua_State* L, Engine& engine, int index) {

    index = lua_absindex(L, index);

    std::vector<std::tuple<int, en::Actor>> entities;

    // Create entities and assign their names.
    lua_pushnil(L);
    while (lua_next(L, index)) {

        auto popValue = lua::PopperOnDestruct(L);
        if (!lua_istable(L, -1)) continue;

        en::Actor actor = makeEntity(L, engine, -1);
        // Save a ref to the entity definition and the actor for adding components later.
        lua_pushvalue(L, -1);
        entities.emplace_back(luaL_ref(L, LUA_REGISTRYINDEX), actor);
    }

    // Add all other components to the entities.
    for (auto[ref, actor] : entities) {

        auto pop = lua::PopperOnDestruct(L);
        lua_rawgeti(L, LUA_REGISTRYINDEX, ref);

        int oldTop = lua_gettop(L);
        addComponents(L, actor, -1);
        int newTop = lua_gettop(L);
        assert(oldTop == newTop);
    }

    // Release the references
    for (auto[ref, actor] : entities)
        luaL_unref(L, LUA_REGISTRYINDEX, ref);
}

Actor ComponentsToLua::makeEntity(lua_State* L, Engine& engine, int entityDefinitionIndex) {

    entityDefinitionIndex = lua_absindex(L, entityDefinitionIndex);
    assert(lua_istable(L, entityDefinitionIndex));

    en::Actor actor = engine.makeActor();

    // Get and assign the name
    auto pop = lua::PopperOnDestruct(L);
    lua_getfield(L, entityDefinitionIndex, "Name");
    if (lua::is<std::string>(L))
        actor.add<en::Name>(lua::to<std::string>(L));

    return actor;
}

void ComponentsToLua::addComponents(lua_State* L, Actor& actor, int entityDefinitionIndex) {

    entityDefinitionIndex = lua_absindex(L, entityDefinitionIndex);

    // Iterate over the entity definition.
    lua_pushnil(L);
    while (lua_next(L, entityDefinitionIndex)) {

        auto popValue = lua::PopperOnDestruct(L);

        // -1: value (component definition)
        // -2: key   (component type name)
        auto componentTypeName = lua::to<std::string>(L, -2);
        if (componentTypeName != "Name") {
            makeComponent(L, actor, componentTypeName, -1);
        }
    }
}

void ComponentsToLua::makeComponent(lua_State* L, Actor& actor, const std::string& componentTypeName, int componentValueIndex) {

    componentValueIndex = lua_absindex(L, componentValueIndex);

    auto& map = getNameToTypeInfoMap();
    auto it = map.find(componentTypeName);
    if (it == map.end()) {
        std::cout << "Unknown component type: " << componentTypeName << std::endl;
        return;
    }
    TypeInfo& typeInfo = it->second;

    int oldTop = lua_gettop(L);

    lua_pushvalue(L, componentValueIndex);
    LuaState stateWrapper = LuaState(L);
    typeInfo.addFromLua(actor, stateWrapper);
    lua_pop(L, 1); // pop the component definition

    int newTop = lua_gettop(L);
    assert(oldTop == newTop);

    if (lua_istable(L, -1)) {

        // TODO make the addFromLua function push the component pointer onto the stack to avoid a second string lookup here.
        pushComponentPointerFromActorByTypeName(L, actor, componentTypeName);
        auto popComponentPointer = PopperOnDestruct(L);
        int componentPointerIndex = lua_gettop(L);

        lua_pushnil(L);
        while (lua_next(L, componentValueIndex)) {

            auto popValue = PopperOnDestruct(L);
            lua_pushvalue(L, -2);
            lua_pushvalue(L, -2);
            lua_settable(L, componentPointerIndex);
        }
    }
}