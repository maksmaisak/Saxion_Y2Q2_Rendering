//
// Created by Maksym Maisak on 2019-02-14.
//

#ifndef SAXION_Y2Q2_RENDERING_UIRECT_H
#define SAXION_Y2Q2_RENDERING_UIRECT_H

#include "glm.hpp"
#include "ComponentsToLua.h"

namespace en {

    struct UIRect {

        LUA_TYPE(UIRect);
        static void initializeMetatable(LuaState& lua);

        glm::vec2 anchorMin = {0, 0};
        glm::vec2 anchorMax = {1, 1};

        glm::vec2 size;
    };
}

#endif //SAXION_Y2Q2_RENDERING_UIRECT_H
