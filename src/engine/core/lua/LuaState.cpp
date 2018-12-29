//
// Created by Maksym Maisak on 29/12/18.
//

#include "LuaState.h"
#include <lua/lua.hpp>

using namespace en;

LuaState::LuaState() : luaStateOwner(luaL_newstate()), L(luaStateOwner.get()) {
    luaL_openlibs(L);
}

int LuaState::doFile(const std::string& filename) {
    return luaL_dofile(L, filename.c_str());
}

