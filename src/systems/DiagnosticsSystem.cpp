//
// Created by Maksym Maisak on 27/10/18.
//

#include "DiagnosticsSystem.h"
#include "GameTime.h"
#include "Engine.h"
#include "Resource.h"
#include "Resources.h"

void DiagnosticsSystem::start() {

    m_fpsCounterPtr = std::make_unique<sf::Text>();
    m_fpsCounterPtr->setFont(*fonts::Diagnostics::get(fonts::paths::Diagnostics));
}

void DiagnosticsSystem::draw() {

    sf::Time frameTime = m_timer.restart();

    m_fpsCounterPtr->setString("fps: " + std::to_string(1000000.0 / frameTime.asMicroseconds()));

    m_engine->getWindow().draw(*m_fpsCounterPtr);
}