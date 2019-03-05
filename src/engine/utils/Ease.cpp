//
// Created by Maksym Maisak on 2019-03-04.
//

#include "Ease.h"
#include <cmath>
#include "glm.hpp"

namespace {

    template<auto in, auto out>
    inline float combinedInOut(float t) {

        const float halfT = t * 2.f;
        return halfT < 1.f ? 0.5f * in(halfT) : 0.5f + 0.5f * out(halfT - 1.f);
    }
}

namespace ease {

    float linear(float t) { return t; }

    float inQuad (float t) { return t * t; }
    float inCubic(float t) { return t * t * t; }
    float inQuart(float t) { return t * t * t * t; }
    float inQuint(float t) { return t * t * t * t * t; }
    float inExpo (float t) { return std::powf(2.f, 10.f * t - 10.f); }
    float inCirc (float t) { return 1.f - std::sqrtf(1.f - t * t); }
    float inSine (float t) { return 1.f - std::cosf(t * glm::half_pi<float>()); }

    float outQuad (float t) { return t -= 1.f, 1.f - t * t; }
    float outCubic(float t) { return t -= 1.f, 1.f + t * t * t; }
    float outQuart(float t) { return t -= 1.f, 1.f - t * t * t * t; }
    float outQuint(float t) { return t -= 1.f, 1.f + t * t * t * t * t; }
    float outExpo (float t) { return 1.f - std::powf(2.f, -10.f * t); }
    float outCirc (float t) { return t -= 1.f, std::sqrtf(1.f - t * t); }
    float outSine (float t) { return std::sinf(t * glm::half_pi<float>()); }

    float inOutQuad (float t) { return combinedInOut<inQuad , outQuad> (t); }
    float inOutCubic(float t) { return combinedInOut<inCubic, outCubic>(t); }
    float inOutQuart(float t) { return combinedInOut<inQuart, outQuart>(t); }
    float inOutQuint(float t) { return combinedInOut<inQuint, outQuint>(t); }
    float inOutExpo (float t) { return combinedInOut<inExpo , outExpo> (t); }
    float inOutCirc (float t) { return combinedInOut<inCirc , outCirc> (t); }
    float inOutSine (float t) { return -0.5f * std::cosf(t * glm::pi<float>()) + 0.5f; }
}
