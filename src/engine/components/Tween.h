//
// Created by Maksym Maisak on 2019-03-04.
//

#ifndef SAXION_Y2Q2_RENDERING_TWEEN_H
#define SAXION_Y2Q2_RENDERING_TWEEN_H

#include "Behavior.h"
#include <functional>
#include "Ease.h"

namespace en {

    struct Tween {

        static void initializeMetatable(LuaState& lua);

        float duration = 1.f;
        std::function<float(float)> ease = ease::inOutQuad;
        std::function<void(float)>  set;

        float progress = 0.f;
    };
}

#endif //SAXION_Y2Q2_RENDERING_TWEEN_H
