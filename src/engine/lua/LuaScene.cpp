//
// Created by Maksym Maisak on 30/12/18.
//

#include "LuaScene.h"
#include <iostream>
#include <lua/lua.hpp>
#include <cassert>
#include <map>
#include <vector>
#include <optional>
#include <tuple>
#include "engine/Engine.h"
#include "engine/core/lua/LuaStack.h"
#include "engine/resources/Resources.h"

#include "engine/core/lua/ComponentsToLua.h"
#include "engine/components/Name.h"
#include "engine/components/Transform.h"
#include "engine/components/RenderInfo.h"
#include "engine/components/Camera.h"
#include "TextureMaterial.hpp"

using namespace en;

LuaScene::LuaScene(const std::string& filename) : m_filename(filename) {}

void LuaScene::open(en::Engine& engine) {

    en::LuaState& lua = engine.getLuaState();

    lua.makeEnvironment();
    auto popEnvironment = lua::PopperOnDestruct(lua);
    if (!lua.loadFile(m_filename)) return;
    lua.setEnvironment(-2);

    auto popFunction = lua::PopperOnDestruct(lua);
    if (!lua.pCall(0, 1)) return;

    makeEntities(engine);
}

/// Goes through the table at the given index, and makes entities out of its fields.
/// First creates all the entities and assigns their names, if provided.
/// Then adds all other components to them.
/// This is necessary to make sure findByName works during component initialization.
void LuaScene::makeEntities(en::Engine& engine, int sceneDefinitionIndex) {

    en::LuaState& lua = engine.getLuaState();
    sceneDefinitionIndex = lua_absindex(lua, sceneDefinitionIndex);

    std::vector<std::tuple<int, en::Actor>> entities;

    // Create entities and assign their names.
    lua_pushnil(lua);
    while (lua_next(lua, sceneDefinitionIndex)) {

        auto popValue = lua::PopperOnDestruct(lua);
        en::Actor actor = makeEntity(engine, -1);

        lua_pushvalue(lua, -1);
        entities.emplace_back(luaL_ref(lua, LUA_REGISTRYINDEX), actor);
    }

    // Add all other components to the entities.
    for (auto[ref, actor] : entities) {

        auto pop = lua::PopperOnDestruct(lua);
        lua_rawgeti(lua, LUA_REGISTRYINDEX, ref);

        int oldTop = lua_gettop(lua);
        addComponents(engine, actor, -1);
        int newTop = lua_gettop(lua);
        assert(oldTop == newTop);
    }

    for (auto[ref, actor] : entities) luaL_unref(lua, LUA_REGISTRYINDEX, ref);
}

en::Actor LuaScene::makeEntity(en::Engine& engine, int entityDefinitionIndex) {

    en::LuaState& lua = engine.getLuaState();
    entityDefinitionIndex = lua_absindex(lua, entityDefinitionIndex);
    assert(lua_istable(lua, entityDefinitionIndex));

    en::Actor actor = engine.makeActor();

    // Get and assign the name
    auto pop = lua::PopperOnDestruct(lua);
    lua_getfield(lua, entityDefinitionIndex, "Name");
    if (lua.is<std::string>()) actor.add<en::Name>(lua.to<std::string>());

    return actor;
}

void LuaScene::addComponents(en::Engine& engine, en::Actor& actor, int entityDefinitionIndex) {

    en::LuaState& lua = engine.getLuaState();
    entityDefinitionIndex = lua_absindex(lua, entityDefinitionIndex);

    // Iterate over the entity definition.
    lua_pushnil(lua);
    while (lua_next(lua, entityDefinitionIndex)) {

        auto popValue = lua::PopperOnDestruct(lua);

        // -1: value (component definition)
        // -2: key   (component type name)
        auto componentTypeName = lua.to<std::string>(-2);
        if (componentTypeName != "Name") {
            ComponentsToLua::makeComponent(actor, componentTypeName, -1);
        }
    }
}
