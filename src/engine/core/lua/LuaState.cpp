//
// Created by Maksym Maisak on 29/12/18.
//

#include "LuaState.h"
#include <lua/lua.hpp>
#include <iostream>

using namespace en;

LuaState::LuaState() : luaStateOwner(luaL_newstate()), L(luaStateOwner.get()) {
    luaL_openlibs(L);
}

bool LuaState::loadFile(const std::string& filename) {

    int errorCode = luaL_loadfile(L, filename.c_str());
    if (errorCode != LUA_OK) {
        printError();
        return false;
    }
    return true;
}

bool LuaState::pCall(int numArgs, int numResults, int messageHandlerIndex) {

    int errorCode = lua_pcall(L, numArgs, numResults, messageHandlerIndex);
    if (errorCode != LUA_OK) {
        printError();
        return false;
    }
    return true;
}

bool LuaState::doFile(const std::string& filename) {
    return loadFile(filename) && pCall(0, 0);
}

bool LuaState::doFileInNewEnvironment(const std::string& filename) {

    makeEnvironment();

    if (!loadFile(filename)) return false;
    setEnvironment(-2);
    return pCall();
}

void LuaState::makeEnvironment() {

    // create table
    lua_newtable(L);
    int tableIndex = lua_gettop(L);

    // create metatable
    lua_newtable(L);
    int metatableIndex = lua_gettop(L);

    // __index = _G
    lua_pushglobaltable(L);
    lua_setfield(L, metatableIndex, "__index");

    // assign metatable
    lua_setmetatable(L, tableIndex);
}

void LuaState::setEnvironment(int environmentIndex) {

    lua_pushvalue(L, environmentIndex);
    lua_setupvalue(L, -2, 1);
}

void LuaState::printError() {

    std::cerr << get<std::string>().value_or("An error occured, but the error message could not be retrieved.") << std::endl;
}