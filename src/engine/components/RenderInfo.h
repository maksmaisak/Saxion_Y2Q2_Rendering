#include <utility>

//
// Created by Maksym Maisak on 24/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_RENDERINFO_H
#define SAXION_Y2Q2_RENDERING_RENDERINFO_H

#include <memory>
#include "Model.h"
#include "AbstractMaterial.hpp"
#include "ComponentsToLua.h"

namespace en {

    struct RenderInfo {

        LUA_TYPE(RenderInfo)
        static RenderInfo& addFromLua(Actor& actor, LuaState& lua);
        static void initializeMetatable(LuaState& lua);

        std::shared_ptr<Model> model;
        std::shared_ptr<AbstractMaterial> material;

        bool isEnabled = true;

        bool isBatchingStatic = false;
        bool isAlreadyBatched = false;
    };
}

#endif //SAXION_Y2Q2_RENDERING_RENDERINFO_H
