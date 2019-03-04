//
// Created by Maksym Maisak on 2019-03-04.
//

#ifndef SAXION_Y2Q2_RENDERING_EASE_H
#define SAXION_Y2Q2_RENDERING_EASE_H

#include <functional>

namespace ease {

    using Ease = std::function<float(float)>;

    float linear(float t);

    float inQuad(float t);

    float outQuad (float t);

    float inOutQuad(float t);
}

#endif //SAXION_Y2Q2_RENDERING_EASE_H
