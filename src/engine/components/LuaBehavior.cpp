//
// Created by Maksym Maisak on 2019-01-31.
//

#include "LuaBehavior.h"

using namespace en;

LuaReference makeLuaBehaviorFromScriptFile(LuaState& lua, const std::string& name) {

    // Load and run the file, expect it to return a factory function
    if (!lua.doFile(name, 1))
        return {};

    if (!lua_isfunction(lua, -1)) {
        lua_pop(lua, 1);
        return {};
    }

    // Call the factory function
    if (!lua.pcall(0, 1))
        return {};

    // Ref the created object and return the reference wrapper.
    return LuaReference(lua);
}

LuaReference getFunctionFromTable(lua_State* L, const std::string& name) {

    lua_getfield(L, -1, name.c_str());
    if (lua_isfunction(L, -1)) {
        return lua::LuaReference(L);
    } else {
        lua_pop(L, 1);
        return {};
    }
}

int LuaBehavior::indexFunction(lua_State* L) {

    // stack:
    // 1 ComponentReference to behavior
    // 2 key

    LuaBehavior& behavior = lua::check<ComponentReference<LuaBehavior>>(L, 1);
    if (!behavior.m_self)
        return 0;

    behavior.m_self.push();
    lua_pushvalue(L, 2);
    lua_gettable(L, -2);
    return 1;
}

int LuaBehavior::newindexFunction(lua_State* L) {

    // stack:
    // 1 behavior
    // 2 key
    // 3 value

    LuaBehavior& behavior = lua::check<ComponentReference<LuaBehavior>>(L, 1);
    if (!behavior.m_self)
        return 0;

    behavior.m_self.push();
    lua_pushvalue(L, 2);
    lua_pushvalue(L, 3);
    lua_settable(L, -3);
    return 0;
}

LuaBehavior& LuaBehavior::addFromLua(Actor& actor, LuaState& lua) {

    auto typeId = lua_type(lua, -1);

    if (typeId == LUA_TTABLE) {
        lua_pushvalue(lua, -1);
        return actor.add<LuaBehavior>(LuaReference(lua));
    }

    if (typeId == LUA_TSTRING) {
        LuaReference ref = makeLuaBehaviorFromScriptFile(lua, lua.to<std::string>());
        if (ref)
            return actor.add<LuaBehavior>(std::move(ref));
    }

    return actor.add<LuaBehavior>();
}

void LuaBehavior::initializeMetatable(LuaState& lua) {

    lua.setField("__index", &indexFunction);
    lua.setField("__newindex", &newindexFunction);
}

LuaBehavior::LuaBehavior(en::Actor actor) : Behavior(actor) {}

LuaBehavior::LuaBehavior(Actor actor, LuaReference&& table) : LuaBehavior(actor) {

    m_self = std::move(table);

    LuaState lua = m_self.getLuaState();

    m_self.push();
    auto popSelf = lua::PopperOnDestruct(lua);

    m_start  = getFunctionFromTable(lua, "start");
    m_update = getFunctionFromTable(lua, "update");

    lua.setField("actor", actor);
}

void LuaBehavior::start() {

    if (!m_start)
        return;

    LuaState lua = m_start.getLuaState();
    assert(lua == m_self.getLuaState());

    m_start.push();
    m_self.push();
    lua.pcall(1, 0);
}

void LuaBehavior::update(float dt) {

    if (!m_update)
        return;

    LuaState lua = m_update.getLuaState();
    assert(lua == m_self.getLuaState());

    m_update.push();
    m_self.push();
    lua.push(dt);
    lua.pcall(2, 0);
}
