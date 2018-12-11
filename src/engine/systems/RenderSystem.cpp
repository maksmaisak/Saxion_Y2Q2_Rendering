//
// Created by Maksym Maisak on 22/10/18.
//

#include "RenderSystem.h"
#include "DrawInfo.h"

namespace en {

    void RenderSystem::draw() {

        auto& renderTarget = m_engine->getWindow();

        // Maybe have the iterator value be a tuple of an en::Entity and components instead of just an Entity?
        for (en::Entity e : m_registry->with<en::Transformable, en::DrawInfo>()) {

            const auto& transform = m_registry->get<en::Transformable>(e).getGlobalTransform();
            renderTarget.draw(*m_registry->get<en::DrawInfo>(e).drawablePtr, transform);
        }
    }
}
