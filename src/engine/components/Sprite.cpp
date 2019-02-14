//
// Created by Maksym Maisak on 2019-02-13.
//

#include "Sprite.h"

using namespace en;

std::shared_ptr<Material> readMaterial(LuaState& lua) {

    lua_getfield(lua, -1, "material");
    auto p = lua::PopperOnDestruct(lua);

    if (lua.is<std::shared_ptr<Material>>())
        return lua.to<std::shared_ptr<Material>>();

    return std::make_shared<Material>(lua);
}

Sprite& Sprite::addFromLua(Actor& actor, LuaState& lua) {

    auto& sprite = actor.add<Sprite>();
    sprite.material = readMaterial(lua);
    return sprite;
}

void Sprite::initializeMetatable(LuaState& lua) {

    lua::addProperty(lua, "isEnabled", lua::property(&Sprite::isEnabled));
}
