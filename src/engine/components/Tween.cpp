//
// Created by Maksym Maisak on 2019-03-04.
//

#include "Tween.h"
#include "Destroy.h"

using namespace en;

void Tween::initializeMetatable(LuaState& lua) {

}

ComponentReference<Tween> Tween::make(EntityRegistry& registry,
    const std::optional<float>& duration,
    const std::optional<ease::Ease>& ease,
    const std::function<void(float)>& set
) {

    Entity e = registry.makeEntity();

    registry.add<Tween>(e,
        duration.value_or(1.f),
        ease.value_or(ease::inOutQuad),
        set
    );

    return ComponentReference<Tween>(registry, e);
}