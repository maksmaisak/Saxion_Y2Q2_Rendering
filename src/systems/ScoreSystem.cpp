//
// Created by Maksym Maisak on 3/11/18.
//

#include "ScoreSystem.h"
#include <string>
#include <cstdint>
#include "State.h"
#include "Resource.h"
#include "Resources.h"

void setOriginNormalized(sf::Text& text, sf::Vector2f coords = {0.5f, 0.5f}) {

    sf::Rect bounds = text.getLocalBounds();
    text.setOrigin({bounds.width * coords.x, bounds.height * coords.y});
}

const unsigned int CharacterSize = 72;

void ScoreSystem::start() {

    sf::Font& font = *fonts::Main::get(fonts::paths::Main);

    m_scoreText.setFont(font);
    m_scoreText.setCharacterSize(CharacterSize);

    const sf::View& view = m_engine->getWindow().getView();
    const sf::Vector2f size = view.getSize();
    const sf::Vector2f position = view.getCenter() + sf::Vector2f(size.x * 0.5f, -size.y * 0.5f);
    m_scoreText.setPosition(position);
}

void ScoreSystem::draw() {

    m_scoreText.setString("Score " + std::to_string(en::State::value<std::uint64_t, "score"_hs>()));
    setOriginNormalized(m_scoreText, {1, 0});
    m_engine->getWindow().draw(m_scoreText);
}

void ScoreSystem::receive(const en::ComponentWillBeRemoved<Asteroid>& info) {

    en::State::value<std::uint64_t, "score"_hs>() += 100;
}

void ScoreSystem::receive(const Restart& info) {

    en::State::value<std::uint64_t, "score"_hs>() = 0;
}
