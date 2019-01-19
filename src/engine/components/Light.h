//
// Created by Maksym Maisak on 24/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_LIGHT_H
#define SAXION_Y2Q2_RENDERING_LIGHT_H

#include "ComponentsToLua.h"
#include "glm.hpp"

namespace en {

    struct Light {

        LUA_TYPE(Light);

        static void addFromLua(Actor& actor, LuaState& lua);
        static void initializeMetatable(LuaState& lua);

        enum class Kind {

            POINT = 0,
            DIRECTIONAL,
            SPOT,

            COUNT
        };

        struct Falloff {

            float constant  = 1;
            float linear    = 0;
            float quadratic = 1;
        };

        Kind kind = Kind::POINT;
        glm::vec3 colorAmbient = {0, 0, 0};
        glm::vec3 color = {1, 1, 1};
        float intensity = 1;
        Falloff falloff = {1, 0, 1};

        // cos of angle in radius
        float spotlightInnerCutoff = glm::cos(glm::radians(40.f));
        float spotlightOuterCutoff = glm::cos(glm::radians(50.f));
    };

    struct FalloffFunctions {

        static constexpr Light::Falloff Constant  = {1, 0, 0};
        static constexpr Light::Falloff Linear    = {1, 1, 0};
        static constexpr Light::Falloff Quadratic = {1, 0, 1};
    };
}

#endif //SAXION_Y2Q2_RENDERING_LIGHT_H
