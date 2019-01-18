#include <utility>

//
// Created by Maksym Maisak on 24/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_RENDERINFO_H
#define SAXION_Y2Q2_RENDERING_RENDERINFO_H

#include <memory>
#include "Mesh.hpp"
#include "AbstractMaterial.hpp"
#include "TextureMaterial.hpp"

#include "ComponentsToLua.h"

namespace en {

    struct RenderInfo {

        LUA_TYPE(RenderInfo)
        static RenderInfo& addFromLua(en::Actor& actor, en::LuaState& lua);

        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<AbstractMaterial> material;
    };

    inline RenderInfo& RenderInfo::addFromLua(en::Actor& actor, en::LuaState& lua) {

        auto& renderInfo = actor.add<en::RenderInfo>();

        if (!lua_istable(lua, -1)) throw "Can't make RenderInfo from a non-table.";

        std::optional<std::string> meshPath = lua.getField<std::string>("mesh");
        if (meshPath) renderInfo.mesh = en::Resources<Mesh>::get("assets/" + *meshPath);

        std::optional<std::string> texturePath = lua.getField<std::string>("texture");
        if (texturePath) renderInfo.material = en::Resources<TextureMaterial>::get("assets/" + *texturePath);

        return renderInfo;
    }
}

#endif //SAXION_Y2Q2_RENDERING_RENDERINFO_H
