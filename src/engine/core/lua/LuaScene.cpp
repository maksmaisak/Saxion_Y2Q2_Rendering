//
// Created by Maksym Maisak on 30/12/18.
//

#include "LuaScene.h"
#include <iostream>
#include <lua.hpp>
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
#include "engine/components/Rigidbody.h"
#include "engine/components/Light.h"
#include "engine/components/Camera.h"
#include "Material.h"

using namespace en;

LuaScene::LuaScene(const std::string& filename) : m_filename(filename) {}
LuaScene::LuaScene(LuaReference&& table) : m_table(std::move(table)) {}

void LuaScene::open() {

    LuaState& lua = getEngine().getLuaState();

    std::cout << "Loading lua-defined scene " + m_filename + "..." << std::endl;

    if (!popTableOnStack())
        return;
    auto popTable = PopperOnDestruct(lua);

    lua_getfield(lua, -1, "update");
    if (lua_isfunction(lua, -1))
        m_update = LuaReference(lua);
    else
        lua_pop(lua, 1);

    lua_getfield(lua, -1, "onCollision");
    if (lua_isfunction(lua, -1))
        m_onCollision = LuaReference(lua);
    else
        lua_pop(lua, 1);

    lua_getfield(lua, -1, "start");
    if (lua_isfunction(lua, -1))
        lua.pcall(0, 0);
    else
        lua_pop(lua, 1);

    std::cout << "Finished loading lua-defined scene." << std::endl;
}

void LuaScene::update(float dt) {

    if (!m_update)
        return;

    LuaState& lua = getEngine().getLuaState();

    m_update.push();
    if (!lua_isfunction(lua, -1)) {
        lua_pop(lua, 1);
        return;
    }

    lua.push(dt);
    lua.pcall(1, 0);
}

void LuaScene::receive(const Collision& collision) {

    Engine& engine = getEngine();
    LuaState& lua = engine.getLuaState();

    m_onCollision.push();
    if (!lua_isfunction(lua, -1)) {
        lua_pop(lua, 1);
        return;
    }

    lua.push(engine.actor(collision.a));
    lua.push(engine.actor(collision.b));
    lua.pcall(2, 0);
}

bool LuaScene::popTableOnStack() {

    LuaState& lua = getEngine().getLuaState();

    if (!m_filename.empty())
        if (lua.doFileInNewEnvironment(m_filename, 1))
            return true;

    if (m_table) {
        m_table.push();
        m_table = {};
        return true;
    }

    return false;
}
