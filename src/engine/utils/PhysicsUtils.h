//
// Created by Maksym Maisak on 23/10/18.
//

#ifndef SAXION_Y2Q1_CPP_PHYSICSUTILS_H
#define SAXION_Y2Q1_CPP_PHYSICSUTILS_H

#include <SFML/Graphics.hpp>
#include <optional>
#include "MyMath.h"

namespace en {

    struct Hit {

        sf::Vector2f normal;
        float timeOfImpact;
        Hit(const sf::Vector2f& normal, float timeOfImpact) : normal(normal), timeOfImpact(timeOfImpact) {}
    };

    inline std::optional<Hit> circleVsCircleContinuous(
        const sf::Vector2f& moverPosition, float moverRadius, const sf::Vector2f& movement,
        const sf::Vector2f& otherPosition, float otherRadius
    ) {

        if (en::isZero(movement)) return std::nullopt;

        sf::Vector2f relativePosition = moverPosition - otherPosition;

        float a = sqrMagnitude(movement);
        float b = 2.f * dot(relativePosition, movement);
        float c =
            sqrMagnitude(relativePosition) -
            (moverRadius + otherRadius) * (moverRadius + otherRadius);

        // If moving out
        if (b >= 0.f) return std::nullopt;

        // If already overlapping.
        if (c < 0.f) return std::make_optional<Hit>(normalized(relativePosition), 0.f);

        float d = b * b - 4.f * a * c;
        if (d < 0.f) return std::nullopt;

        float t = (-b - sqrtf(d)) / (2.f * a);

        if (t <  0.f) return std::nullopt;
        if (t >= 1.f) return std::nullopt;

        return std::make_optional<Hit>(normalized(relativePosition + movement * t), t);
    }

    /// A helper for resolving collisions between physical bodies
    /// in a way which obeys conservation of momentum.
    /// Assumes `normal` is normalized.
    inline void resolve(
        sf::Vector2f& aVelocity, float aInverseMass,
        sf::Vector2f& bVelocity, float bInverseMass,
        sf::Vector2f normal, float bounciness = 1.f
    ) {
        float aSpeedAlongNormal = en::dot(normal, aVelocity);
        float bSpeedAlongNormal = en::dot(normal, bVelocity);

        if (aSpeedAlongNormal - bSpeedAlongNormal > 0.f) return;

        float u =
            (aSpeedAlongNormal * bInverseMass + bSpeedAlongNormal * aInverseMass) /
            (aInverseMass + bInverseMass);

        float aDeltaSpeedAlongNormal = -(1.f + bounciness) * (aSpeedAlongNormal - u);
        aVelocity += normal * aDeltaSpeedAlongNormal;

        float bDeltaSpeedAlongNormal = -(1.f + bounciness) * (bSpeedAlongNormal - u);
        bVelocity += normal * bDeltaSpeedAlongNormal;
    }
}

#endif //SAXION_Y2Q1_CPP_PHYSICSUTILS_H
