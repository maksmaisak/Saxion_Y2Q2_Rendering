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

        // In normalized coordinates [0..1]
        glm::vec2 anchorMin = {0, 0};
        glm::vec2 anchorMax = {1, 1};

        // In pixels
        glm::vec2 offsetMin = {0, 0};
        glm::vec2 offsetMax = {0, 0};

        bool isEnabled = true;

        glm::vec2 computedMin;
        glm::vec2 computedMax;
        glm::vec2 computedSize;
        bool isMouseOver = false;
        bool wasMouseOver = false;
    };
}

#endif //SAXION_Y2Q2_RENDERING_UIRECT_H
