#include <utility>

//
// Created by Maksym Maisak on 24/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_RENDERINFO_H
#define SAXION_Y2Q2_RENDERING_RENDERINFO_H

#include <memory>
#include "Mesh.hpp"
#include "AbstractMaterial.hpp"
#include "ComponentsToLua.h"

namespace en {

    struct RenderInfo {

        LUA_TYPE(RenderInfo)
        static RenderInfo& addFromLua(Actor& actor, LuaState& lua);
        static void initializeMetatable(LuaState& lua);

        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<AbstractMaterial> material;

        bool isEnabled = true;
    };
}

#endif //SAXION_Y2Q2_RENDERING_RENDERINFO_H
