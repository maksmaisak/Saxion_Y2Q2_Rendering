//
// Created by Maksym Maisak on 22/10/18.
//

#ifndef SAXION_Y2Q1_CPP_RENDERSYSTEM_H
#define SAXION_Y2Q1_CPP_RENDERSYSTEM_H

#include <memory>
#include "System.h"
#include "Engine.h"
#include "DebugHud.hpp"

namespace en {
    class RenderSystem : public System {

    public:
        RenderSystem(bool displayMeshDebugInfo = false);
        void start() override;
        void draw() override;

    private:
        Actor getMainCamera();
        std::unique_ptr<DebugHud> m_debugHud;
        bool m_displayMeshDebugInfo;
    };
}

#endif //SAXION_Y2Q1_CPP_RENDERSYSTEM_H
