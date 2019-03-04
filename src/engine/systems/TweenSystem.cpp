//
// Created by Maksym Maisak on 2019-03-04.
//

#include "TweenSystem.h"
#include <vector>
#include "EntityRegistry.h"
#include "Tween.h"
#include "Destroy.h"

using namespace en;

namespace {

    inline void markForDestruction(EntityRegistry& registry, Entity e) {

        if (!registry.tryGet<Destroy>(e))
            registry.add<Destroy>(e);
    }
}

void TweenSystem::update(float dt) {

    for (Entity e : m_registry->with<Tween>()) {

        if (m_registry->tryGet<Destroy>(e))
            continue;

        auto& tween = m_registry->get<Tween>(e);
        if (tween.target && !m_registry->isAlive(tween.target)) {
            markForDestruction(*m_registry, e);
            return;
        }

        tween.progress += dt / tween.duration;
        if (tween.progress >= 1.f) {
            tween.progress = 1.f;
            markForDestruction(*m_registry, e);
        }

        const float t = tween.ease(tween.progress);
        tween.set(t);
    }
}
