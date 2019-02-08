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

    class ShaderProgram;
    class Light;
    class Transform;

    class RenderSystem : public System {

    public:
        RenderSystem(bool displayMeshDebugInfo = false);
        void start() override;
        void draw() override;

    private:
        Actor getMainCamera();
        void updateDepthMaps();

        void updateDepthMapDirectionalLight(const Light& light, const Transform& lightTransform);
        void updateDepthMapPositionalLight(const Light& light, const Transform& lightTransform);

        std::shared_ptr<ShaderProgram> m_depthShaderDirectional;
        std::shared_ptr<ShaderProgram> m_depthShaderPositional;

        std::unique_ptr<DebugHud> m_debugHud;
        bool m_displayMeshDebugInfo = false;
    };
}

#endif //SAXION_Y2Q1_CPP_RENDERSYSTEM_H
