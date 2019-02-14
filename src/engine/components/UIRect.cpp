//
// Created by Maksym Maisak on 2019-02-14.
//

#include "UIRect.h"

using namespace en;

void UIRect::initializeMetatable(LuaState& lua) {

    lua::addProperty(lua, "anchorMin", lua::property(&UIRect::anchorMin));
    lua::addProperty(lua, "anchorMax", lua::property(&UIRect::anchorMax));
    lua::addProperty(lua, "offsetMin", lua::property(&UIRect::offsetMin));
    lua::addProperty(lua, "offsetMax", lua::property(&UIRect::offsetMax));
}