//
// Created by Maksym Maisak on 2019-02-12.
//

#include "Camera.h"

using namespace en;

void Camera::initializeMetatable(en::Actor& actor, en::LuaState& lua) {

    lua::addProperty(lua, "isOrthographic", lua::property(&Camera::isOrthographic));
    lua::addProperty(lua, "fov", lua::property(&Camera::fov));
    lua::addProperty(lua, "nearPlaneDistance", lua::property(&Camera::nearPlaneDistance));
    lua::addProperty(lua, "farPlaneDistance" , lua::property(&Camera::farPlaneDistance));
}
