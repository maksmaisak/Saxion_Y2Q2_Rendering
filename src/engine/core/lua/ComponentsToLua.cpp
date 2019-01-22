//
// Created by Maksym Maisak on 31/12/18.
//

#include "ComponentsToLua.h"
#include <cassert>
#include <iostream>

#include "Name.h"

using namespace en;

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

void ComponentsToLua::pushComponentPointerFromActorByTypeName(Actor& actor, const std::string& componentTypeName) {

    auto& lua = actor.getEngine().getLuaState();

    auto& map = getNameToTypeInfoMap();
    auto it = map.find(componentTypeName);
    if (it == map.end()) {
        std::cout << "Unknown component type: " << componentTypeName << std::endl;
        lua_pushnil(lua);
        return;
    }

    it->second.pushFromActor(actor, lua);
}

void ComponentsToLua::addComponentToActorByTypeName(Actor& actor, const std::string& componentTypeName) {

    auto& lua = actor.getEngine().getLuaState();

    auto& map = getNameToTypeInfoMap();
    auto it = map.find(componentTypeName);
    if (it == map.end()) {
        std::cout << "Unknown component type: " << componentTypeName << std::endl;
        lua_pushnil(lua);
        return;
    }

    it->second.addToActor(actor, lua);
}

void ComponentsToLua::makeEntities(Engine& engine, int index) {

    en::LuaState& lua = engine.getLuaState();
    index = lua_absindex(lua, index);

    std::vector<std::tuple<int, en::Actor>> entities;

    // Create entities and assign their names.
    lua_pushnil(lua);
    while (lua_next(lua, index)) {

        auto popValue = lua::PopperOnDestruct(lua);
        if (!lua_istable(lua, -1)) continue;

        en::Actor actor = makeEntity(engine, -1);
        // Save a ref to the entity definition and the actor for adding components later.
        lua_pushvalue(lua, -1);
        entities.emplace_back(luaL_ref(lua, LUA_REGISTRYINDEX), actor);
    }

    // Add all other components to the entities.
    for (auto[ref, actor] : entities) {

        auto pop = lua::PopperOnDestruct(lua);
        lua_rawgeti(lua, LUA_REGISTRYINDEX, ref);

        int oldTop = lua_gettop(lua);
        addComponents(actor, -1);
        int newTop = lua_gettop(lua);
        assert(oldTop == newTop);
    }

    // Release the references
    for (auto[ref, actor] : entities)
        luaL_unref(lua, LUA_REGISTRYINDEX, ref);
}

Actor ComponentsToLua::makeEntity(Engine& engine, int entityDefinitionIndex) {

    en::LuaState& lua = engine.getLuaState();

    entityDefinitionIndex = lua_absindex(lua, entityDefinitionIndex);
    assert(lua_istable(lua, entityDefinitionIndex));

    en::Actor actor = engine.makeActor();

    // Get and assign the name
    auto pop = lua::PopperOnDestruct(lua);
    lua_getfield(lua, entityDefinitionIndex, "Name");
    if (lua.is<std::string>())
        actor.add<en::Name>(lua.to<std::string>());

    return actor;
}

void ComponentsToLua::addComponents(Actor& actor, int entityDefinitionIndex) {

    en::LuaState& lua = actor.getEngine().getLuaState();
    entityDefinitionIndex = lua_absindex(lua, entityDefinitionIndex);

    // Iterate over the entity definition.
    lua_pushnil(lua);
    while (lua_next(lua, entityDefinitionIndex)) {

        auto popValue = lua::PopperOnDestruct(lua);

        // -1: value (component definition)
        // -2: key   (component type name)
        auto componentTypeName = lua.to<std::string>(-2);
        if (componentTypeName != "Name") {
            makeComponent(actor, componentTypeName, -1);
        }
    }
}

void ComponentsToLua::makeComponent(Actor& actor, const std::string& componentTypeName, int componentValueIndex) {

    auto& lua = actor.getEngine().getLuaState();
    componentValueIndex = lua_absindex(lua, componentValueIndex);

    auto& map = getNameToTypeInfoMap();
    auto it = map.find(componentTypeName);
    if (it == map.end()) {
        std::cout << "Unknown component type: " << componentTypeName << std::endl;
        return;
    }

    int oldTop = lua_gettop(lua);
    lua_pushvalue(lua, componentValueIndex);
    it->second.addFromLua(actor, lua);
    lua_pop(lua, 1);
    int newTop = lua_gettop(lua);
    assert(oldTop == newTop);

    if (!lua_istable(lua, -1)) return;

    // TODO make the addFromLua function push the component pointer onto the stack to avoid a second string lookup here.
    pushComponentPointerFromActorByTypeName(actor, componentTypeName);
    auto popComponentPointer = PopperOnDestruct(lua);
    int componentPointerIndex = lua_gettop(lua);

    lua_pushnil(lua);
    while (lua_next(lua, componentValueIndex)) {

        auto popValue = PopperOnDestruct(lua);
        lua_pushvalue(lua, -2);
        lua_pushvalue(lua, -2);
        lua_settable(lua, componentPointerIndex);
    }
}