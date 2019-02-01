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

LuaBehavior& LuaBehavior::addFromLua(Actor& actor, LuaState& lua) {

    auto typeId = lua_type(lua, -1);

    if (typeId == LUA_TSTRING) {

        LuaReference ref = makeLuaBehaviorFromScriptFile(lua, lua.to<std::string>());
        if (ref)
            return actor.add<LuaBehavior>(std::move(ref));
    }

    return actor.add<LuaBehavior>();
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

LuaBehavior::LuaBehavior(en::Actor actor) : Behavior(actor) {}

LuaBehavior::LuaBehavior(Actor actor, LuaReference&& table) : LuaBehavior(actor) {

    m_self = std::move(table);

    LuaState lua = m_self.getLuaState();

    m_self.push();

    m_start  = getFunctionFromTable(lua, "start");
    m_update = getFunctionFromTable(lua, "update");

    lua.setField("actor", actor);

    lua_pop(lua, 1);
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
