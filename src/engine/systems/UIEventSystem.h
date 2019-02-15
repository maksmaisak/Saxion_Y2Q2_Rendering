//
// Created by Maksym Maisak on 2019-02-14.
//

#ifndef SAXION_Y2Q2_RENDERING_UIEVENTSYSTEM_H
#define SAXION_Y2Q2_RENDERING_UIEVENTSYSTEM_H

#include "System.h"
#include "Entity.h"
#include "glm.hpp"

namespace en {

    class UIRect;

    class UIEventSystem : public System {

    public:
        void update(float dt) override;

    private:
        void updateRect(Entity e, UIRect& rect, const glm::vec2& mousePosition);
    };
}

#endif //SAXION_Y2Q2_RENDERING_UIEVENTSYSTEM_H
