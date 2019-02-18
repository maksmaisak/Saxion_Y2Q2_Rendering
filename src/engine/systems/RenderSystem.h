//
// Created by Maksym Maisak on 22/10/18.
//

#ifndef SAXION_Y2Q1_CPP_RENDERSYSTEM_H
#define SAXION_Y2Q1_CPP_RENDERSYSTEM_H

#include <memory>
#include <vector>
#include <GL/glew.h>
#include "Entity.h"
#include "System.h"
#include "Engine.h"
#include "DebugHud.hpp"
#include "DepthMaps.h"
#include "VertexRenderer.h"

namespace en {

    class ShaderProgram;
    class UIRect;
    class Transform;

    class RenderSystem : public System {

    public:
        RenderSystem(bool displayMeshDebugInfo = false);
        void start() override;
        void draw() override;

    private:
        void updateDepthMaps();
        void renderEntities();
        void renderUI();
        void renderDebug();

        Actor getMainCamera();
        void updateDepthMapsDirectionalLights(const std::vector<Entity>& directionalLights);
        void updateDepthMapsPositionalLights(const std::vector<Entity>& pointLights);

        void renderUIRect(Entity entity, UIRect& rect);
        glm::vec2 getWindowSize();
        float getUIScaleFactor();

        DepthMaps m_depthMaps;
        std::shared_ptr<ShaderProgram> m_directionalDepthShader;
        std::shared_ptr<ShaderProgram> m_positionalDepthShader;

        VertexRenderer m_vertexRenderer;
        glm::vec2 m_referenceResolution;

        std::unique_ptr<DebugHud> m_debugHud;
        bool m_displayMeshDebugInfo = false;
    };
}

#endif //SAXION_Y2Q1_CPP_RENDERSYSTEM_H
