//
// Created by Maksym Maisak on 24/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_CAMERA_H
#define SAXION_Y2Q2_RENDERING_CAMERA_H

#include "glm.hpp"
#include "ComponentsToLua.h"

namespace en {

    struct Camera {

        LUA_TYPE(Camera)

        // TODO Camera settings. field-of-view etc. Lazy-evaluate this out of settings.
        glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 1000.0f);
    };
}

#endif //SAXION_Y2Q2_RENDERING_CAMERA_H
