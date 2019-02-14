//
// Created by Maksym Maisak on 2019-02-14.
//

#ifndef SAXION_Y2Q2_RENDERING_UIEVENTSYSTEM_H
#define SAXION_Y2Q2_RENDERING_UIEVENTSYSTEM_H

#include "System.h"
#include "Entity.h"

namespace en {

    class UIEventSystem : public System {

    public:
        void start() override;
        void update(float dt) override;
    };
}

#endif //SAXION_Y2Q2_RENDERING_UIEVENTSYSTEM_H
