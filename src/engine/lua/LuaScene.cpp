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

LuaScene::~LuaScene() {

    luaL_unref(m_engine->getLuaState(), LUA_REGISTRYINDEX, m_luaUpdateFunctionRef);
}

void LuaScene::open(en::Engine& engine) {

    m_engine = &engine;
    en::LuaState& lua = m_engine->getLuaState();

    std::cout << "Loading lua-defined scene " + m_filename + "..." << std::endl;

    lua.makeEnvironment();
    auto popEnvironment = lua::PopperOnDestruct(lua);
    if (!lua.loadFile(m_filename)) return;
    lua.setEnvironment(-2);

    auto popFunction = lua::PopperOnDestruct(lua);
    if (!lua.pCall(0, 1)) return;

    makeEntities(-1);
    std::cout << "Finished loading lua-defined scene." << std::endl;
}

/// Goes through the table at the given index, and makes entities out of its fields.
/// First creates all the entities and assigns their names, if provided.
/// Then adds all other components to them.
/// This is necessary to make sure findByName works during component initialization.
void LuaScene::makeEntities(int sceneDefinitionIndex) {

    en::LuaState& lua = m_engine->getLuaState();
    sceneDefinitionIndex = lua_absindex(lua, sceneDefinitionIndex);

    std::vector<std::tuple<int, en::Actor>> entities;

    // Create entities and assign their names.
    lua_pushnil(lua);
    while (lua_next(lua, sceneDefinitionIndex)) {

        auto popValue = lua::PopperOnDestruct(lua);

        if (lua_istable(lua, -1)) {

            en::Actor actor = makeEntity(-1);

            // Save a ref to the entity definition and the actor for adding components later.
            lua_pushvalue(lua, -1);
            entities.emplace_back(luaL_ref(lua, LUA_REGISTRYINDEX), actor);

        } else if (lua_isfunction(lua, -1)) {

            if (lua.is<std::string>(-2) && lua.to<std::string>(-2) == "update") {
                lua_pushvalue(lua, -1);
                m_luaUpdateFunctionRef = luaL_ref(lua, LUA_REGISTRYINDEX);
            }
        }
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

    for (auto[ref, actor] : entities) luaL_unref(lua, LUA_REGISTRYINDEX, ref);
}

en::Actor LuaScene::makeEntity(int entityDefinitionIndex) {

    en::LuaState& lua = m_engine->getLuaState();

    entityDefinitionIndex = lua_absindex(lua, entityDefinitionIndex);
    assert(lua_istable(lua, entityDefinitionIndex));

    en::Actor actor = m_engine->makeActor();

    // Get and assign the name
    auto pop = lua::PopperOnDestruct(lua);
    lua_getfield(lua, entityDefinitionIndex, "Name");
    if (lua.is<std::string>()) actor.add<en::Name>(lua.to<std::string>());

    return actor;
}

void LuaScene::addComponents( en::Actor& actor, int entityDefinitionIndex) {

    en::LuaState& lua = m_engine->getLuaState();
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

void LuaScene::update(float dt) {

    if (m_luaUpdateFunctionRef == LUA_NOREF) return;

    auto& lua = m_engine->getLuaState();

    lua_rawgeti(lua, LUA_REGISTRYINDEX, m_luaUpdateFunctionRef);
    if (lua_isnil(lua, -1)) {
        lua_pop(lua, -1);
        return;
    }

    lua_pushnumber(lua, dt);
    lua.pCall(1, 0);
}
