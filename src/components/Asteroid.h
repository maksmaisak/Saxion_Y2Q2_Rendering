//
// Created by Maksym Maisak on 24/10/18.
//

#ifndef SAXION_Y2Q1_CPP_ASTEROID_H
#define SAXION_Y2Q1_CPP_ASTEROID_H

#include <utility>

struct Asteroid {

    enum class Size {
        Small  = 0,
        Medium = 1,
        Large  = 2
    };

    struct Config {
        float averageRadius;
        float radiusRange;
    };

    Size size = Size::Large;

    static const Config& getConfig(Size size) {

        static const Config configsBySize[] {
            {20.f, 4.f }, // Small
            {40.f, 7.f }, // Medium
            {60.f, 10.f}  // Large
        };

        return configsBySize[static_cast<std::size_t>(size)];
    }
};

#endif //SAXION_Y2Q1_CPP_ASTEROID_H
