//
// Created by Maksym Maisak on 2019-03-04.
//

#include "Ease.h"

namespace ease {

    float linear(float t) { return t; }

    float inQuad(float t) { return t * t; }

    float outQuad(float t) { return t * (2.f - t); }

    float inOutQuad(float t) {

        const float half = t * 2.f;
        return half < 1.f ? 0.5f * inQuad(half) : 0.5f + 0.5f * outQuad(half - 1);
    }
}
