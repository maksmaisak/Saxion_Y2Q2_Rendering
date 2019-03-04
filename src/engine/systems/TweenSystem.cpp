//
// Created by Maksym Maisak on 2019-03-04.
//

#include "TweenSystem.h"
#include <vector>
#include "EntityRegistry.h"
#include "Tween.h"
#include "Destroy.h"

using namespace en;

void TweenSystem::update(float dt) {

    for (Entity e : m_registry->with<Tween>()) {

        auto& tween = m_registry->get<Tween>(e);

        tween.progress += dt / tween.duration;
        if (tween.progress >= 1.f) {
            tween.progress = 1.f;

            if (!m_registry->tryGet<Destroy>(e))
                m_registry->add<Destroy>(e);
        }

        float t = tween.ease(tween.progress);
        tween.set(t);
    }
}
