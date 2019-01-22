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

LuaScene::~LuaScene() {

    luaL_unref(getEngine().getLuaState(), LUA_REGISTRYINDEX, m_luaUpdateFunctionRef);
}

void LuaScene::open() {

    en::LuaState& lua = getEngine().getLuaState();

    std::cout << "Loading lua-defined scene " + m_filename + "..." << std::endl;

    bool didLoad = lua.doFileInNewEnvironment(m_filename, 1);
    if (!didLoad)
        return;
    auto popTable = PopperOnDestruct(lua);

    lua_getfield(lua, -1, "update");
    if (lua_isfunction(lua, -1))
        m_luaUpdateFunctionRef = luaL_ref(lua, LUA_REGISTRYINDEX);
    else
        lua_pop(lua, 1);

    lua_getfield(lua, -1, "start");
    if (lua_isfunction(lua, -1))
        lua.pCall(0, 0);
    else
        lua_pop(lua, 1);

    std::cout << "Finished loading lua-defined scene." << std::endl;
}

void LuaScene::update(float dt) {

    if (m_luaUpdateFunctionRef == LUA_NOREF) return;

    auto& lua = getEngine().getLuaState();

    lua_rawgeti(lua, LUA_REGISTRYINDEX, m_luaUpdateFunctionRef);
    if (!lua_isfunction(lua, -1)) {
        lua_pop(lua, 1);
        return;
    }

    lua.push(dt);
    lua.pCall(1, 0);
}
