//
// Created by Maksym Maisak on 24/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_LIGHT_H
#define SAXION_Y2Q2_RENDERING_LIGHT_H

#include "ComponentsToLua.h"
#include "glm.hpp"

namespace en {

    struct Light {

        LUA_COMPONENT_TYPE(Light);

        enum class Kind {
            POINT,
            DIRECTIONAL
        };

        Kind kind = Kind::POINT;
        glm::vec3 color = {1, 1, 1};
    };
}

#endif //SAXION_Y2Q2_RENDERING_LIGHT_H
