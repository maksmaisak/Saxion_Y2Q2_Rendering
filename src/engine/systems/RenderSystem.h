//
// Created by Maksym Maisak on 22/10/18.
//

#ifndef SAXION_Y2Q1_CPP_RENDERSYSTEM_H
#define SAXION_Y2Q1_CPP_RENDERSYSTEM_H

#include <memory>
#include <vector>
#include <unordered_map>
#include <GL/glew.h>
#include "Entity.h"
#include "System.h"
#include "Engine.h"
#include "DebugHud.hpp"
#include "DepthMaps.h"
#include "VertexRenderer.h"
#include "ComponentPool.h"
#include "Receiver.h"
#include "SceneManager.h"

namespace en {

    class ShaderProgram;
    class UIRect;
    class Material;
    class Mesh;

    class RenderSystem : public System, Receiver<SceneManager::OnSceneClosed> {

    public:
        explicit RenderSystem(bool displayMeshDebugInfo = false);
        void start() override;
        void draw() override;

    private:
        void receive(const SceneManager::OnSceneClosed& info) override;

        void updateBatches();
        void updateDepthMaps();
        void renderEntities();
        void renderUI();
        void renderDebug();

        Actor getMainCamera();
        void updateDepthMapsDirectionalLights(const std::vector<Entity>& directionalLights);
        void updateDepthMapsPositionalLights (const std::vector<Entity>& pointLights);

        void renderUIRect(Entity entity, UIRect& rect);
        glm::vec2 getWindowSize();
        float getUIScaleFactor();

        DepthMaps m_depthMaps;
        std::shared_ptr<ShaderProgram> m_directionalDepthShader;
        std::shared_ptr<ShaderProgram> m_positionalDepthShader;

        std::unordered_map<std::shared_ptr<Material>, Mesh> m_batches;

        VertexRenderer m_vertexRenderer;
        glm::vec2 m_referenceResolution;

        std::unique_ptr<DebugHud> m_debugHud;
        bool m_displayMeshDebugInfo = false;
    };
}

#endif //SAXION_Y2Q1_CPP_RENDERSYSTEM_H
