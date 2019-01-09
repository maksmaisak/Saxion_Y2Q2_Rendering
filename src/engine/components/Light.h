//
// Created by Maksym Maisak on 24/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_LIGHT_H
#define SAXION_Y2Q2_RENDERING_LIGHT_H

#include "ComponentsToLua.h"

namespace en {

    struct Light {

        LUA_COMPONENT_TYPE(Light);

        // TODO light settings. Kind, intensity etc.
    };
}

#endif //SAXION_Y2Q2_RENDERING_LIGHT_H
