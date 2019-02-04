//
// Created by Maksym Maisak on 2019-01-19.
//

#include "RenderInfo.h"
#include <memory>
#include "Material.h"

using namespace en;

std::shared_ptr<Material> readMaterial(RenderInfo& renderInfo, LuaState& lua) {

    lua_getfield(lua, -1, "material");
    auto p = lua::PopperOnDestruct(lua);

    if (lua.is<std::shared_ptr<Material>>()) {
        return lua.to<std::shared_ptr<Material>>();
    }

    return std::make_shared<Material>(lua);
}

RenderInfo& RenderInfo::addFromLua(Actor& actor, LuaState& lua) {

    auto& renderInfo = actor.add<en::RenderInfo>();
    renderInfo.material = readMaterial(renderInfo, lua);
    return renderInfo;
}

void RenderInfo::initializeMetatable(LuaState& lua) {

    lua::addProperty(lua, "mesh", lua::writeonlyProperty([](ComponentReference<RenderInfo>& renderInfo, const std::string& value) {
        renderInfo->mesh = en::Resources<Mesh>::get("assets/" + value);
    }));
}
