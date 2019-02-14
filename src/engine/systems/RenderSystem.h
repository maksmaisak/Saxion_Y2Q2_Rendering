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
        void renderUIRects(const std::vector<Entity>& rects, glm::vec2 parentMin, glm::vec2 parentMax);
        void renderUIRect(Entity entity, glm::vec2 min, glm::vec2 max);
        glm::vec2 getWindowSize();

        DepthMaps m_depthMaps;
        std::shared_ptr<ShaderProgram> m_directionalDepthShader;
        std::shared_ptr<ShaderProgram> m_positionalDepthShader;

        VertexRenderer m_vertexRenderer;

        std::unique_ptr<DebugHud> m_debugHud;
        bool m_displayMeshDebugInfo = false;
    };
}

#endif //SAXION_Y2Q1_CPP_RENDERSYSTEM_H
