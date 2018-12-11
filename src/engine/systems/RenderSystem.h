//
// Created by Maksym Maisak on 22/10/18.
//

#ifndef SAXION_Y2Q1_CPP_RENDERSYSTEM_H
#define SAXION_Y2Q1_CPP_RENDERSYSTEM_H

#include "System.h"
#include "Engine.h"

namespace en {
    class RenderSystem : public System {
    public:
        void draw() override;
    };
}

#endif //SAXION_Y2Q1_CPP_RENDERSYSTEM_H
