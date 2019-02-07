//
// Created by Maksym Maisak on 2019-01-13.
//

#include "LightPropertyAnimator.h"
#include "Light.h"
#include "glm.hpp"

void LightPropertyAnimator::start() {

    auto& light = actor().get<en::Light>();
    m_initialLightSettings = light.getSettings();
    m_initialLightKind = light.getKind();

    m_startTime = GameTime::now();
}

void LightPropertyAnimator::update(float dt) {

    auto& light = m_actor.get<en::Light>();

    const float time = (GameTime::now() - m_startTime).asSeconds();
    const float sinTime = glm::sin(time);

    const auto rotateColor = [&](const glm::vec3& color) {
        return glm::abs(glm::rotate(color, time, {1, 1, 1}));
    };

    auto& settings = light.getSettings();
    settings.color = rotateColor(m_initialLightSettings.color);
    settings.colorAmbient = rotateColor(m_initialLightSettings.colorAmbient);
    settings.spotlightInnerCutoff = m_initialLightSettings.spotlightInnerCutoff * sinTime;
    settings.spotlightOuterCutoff = m_initialLightSettings.spotlightOuterCutoff * sinTime;
    settings.falloff.linear    = glm::abs(sinTime);
    settings.falloff.quadratic = 1.f - glm::abs(sinTime);

    auto kind = (en::Light::Kind)(((int)m_initialLightKind + (int)(time / 4.f)) % (int)en::Light::Kind::COUNT);
    light.setKind(kind);
}
