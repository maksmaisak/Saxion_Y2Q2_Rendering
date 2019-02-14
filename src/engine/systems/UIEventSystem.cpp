//
// Created by Maksym Maisak on 2019-02-14.
//

#include "UIEventSystem.h"
#include "Engine.h"
#include "EntityRegistry.h"
#include "Transform.h"
#include "UIRect.h"
#include "UIEvents.h"
#include <SFML/Graphics.hpp>

using namespace en;

void UIEventSystem::update(float dt) {

    constexpr std::size_t numButtons = 5;
    const bool isMouseButtonDown[numButtons] = {
        sf::Mouse::isButtonPressed(sf::Mouse::Button::Left),
        sf::Mouse::isButtonPressed(sf::Mouse::Button::Right),
        sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle),
        sf::Mouse::isButtonPressed(sf::Mouse::Button::XButton1),
        sf::Mouse::isButtonPressed(sf::Mouse::Button::XButton2),
    };

    sf::RenderWindow& window = m_engine->getWindow();
    sf::Vector2i temp = sf::Mouse::getPosition(window);
    glm::vec2 mousePosition = {temp.x, window.getSize().y - temp.y};

    for (Entity e : m_registry->with<UIRect>()) {

        auto& rect = m_registry->get<UIRect>(e);
        rect.wasMouseOver = rect.isMouseOver;
        rect.isMouseOver = glm::all(glm::lessThan(rect.computedMin, mousePosition)) && glm::all(glm::lessThan(mousePosition, rect.computedMax));

        if (rect.isMouseOver && !rect.wasMouseOver)
            Receiver<MouseEnter>::broadcast(e);

        if (rect.isMouseOver)
            Receiver<MouseOver>::broadcast(e);

        if (!rect.isMouseOver && rect.wasMouseOver)
            Receiver<MouseLeave>::broadcast(e);

        for (int i = 0; i < numButtons; ++i) {

            if (isMouseButtonDown[i])
                Receiver<MouseDown>::broadcast(e, i + 1);
        }
    }
}
