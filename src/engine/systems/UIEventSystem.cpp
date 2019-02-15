//
// Created by Maksym Maisak on 2019-02-14.
//

#include "UIEventSystem.h"
#include "Engine.h"
#include "EntityRegistry.h"
#include "Transform.h"
#include "UIRect.h"
#include "UIEvents.h"
#include "MouseHelper.h"

using namespace en;

void UIEventSystem::update(float dt) {

    glm::vec2 mousePosition = utils::MouseHelper::getPosition(m_engine->getWindow());

    for (Entity e : m_registry->with<UIRect>()) {

        auto& rect = m_registry->get<UIRect>(e);
        rect.wasMouseOver = rect.isMouseOver;
        rect.isMouseOver = glm::all(glm::lessThan(rect.computedMin, mousePosition)) && glm::all(glm::lessThan(mousePosition, rect.computedMax));
        if (!rect.isEnabled)
            continue;

        if (rect.isMouseOver && !rect.wasMouseOver)
            Receiver<MouseEnter>::broadcast(e);

        if (rect.isMouseOver)
            Receiver<MouseOver>::broadcast(e);

        if (!rect.isMouseOver && rect.wasMouseOver)
            Receiver<MouseLeave>::broadcast(e);

        if (rect.isMouseOver) {
            for (int i = 0; i < sf::Mouse::ButtonCount; ++i) {
                auto buttonCode = (sf::Mouse::Button)i;

                if (utils::MouseHelper::isDown(buttonCode))
                    Receiver<MouseDown>::broadcast(e, i + 1);

                if (utils::MouseHelper::isHeld(buttonCode))
                    Receiver<MouseHold>::broadcast(e, i + 1);

                if (utils::MouseHelper::isUp(buttonCode))
                    Receiver<MouseUp>::broadcast(e, i + 1);
            }
        }
    }
}
