//
// Created by Maksym Maisak on 22/10/18.
//

#include "RenderSystem.h"
#include <iostream>
#include "components/RenderInfo.h"
#include "components/Transform.h"
#include "components/Camera.h"
#include "components/Name.h"
#include "GLHelpers.h"

namespace en {

    RenderSystem::RenderSystem(bool displayMeshDebugInfo) :
        m_displayMeshDebugInfo(displayMeshDebugInfo) {}

    void enableDebug();

    void RenderSystem::start() {

        glEnable(GL_DEPTH_TEST);

        // Counterclockwise vertex order
        glFrontFace(GL_CCW);

        // Enable back face culling
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        // Set the default blend mode
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //glClearColor((float)0x2d / 0xff, (float)0x6b / 0xff, (float)0xce / 0xff, 1.0f);
        glClearColor(0, 0, 0, 1);

        glEnable(GL_FRAMEBUFFER_SRGB);

        m_debugHud = std::make_unique<DebugHud>(&m_engine->getWindow());
    }

    void RenderSystem::draw() {

        if (glCheckError() != GL_NO_ERROR) {
            std::cerr << "Uncaught openGL error(s) before rendering." << std::endl;
        }

        Actor mainCamera = getMainCamera();
        if (mainCamera) {

            glm::mat4 matrixView = glm::inverse(mainCamera.get<Transform>().getWorldTransform());
            glm::mat4 matrixProjection = mainCamera.get<Camera>().projectionMatrix;

            for (Entity e : m_registry->with<Transform, RenderInfo>()) {

                auto& renderInfo = m_registry->get<RenderInfo>(e);
                if (!renderInfo.material || !renderInfo.mesh) continue;

                glm::mat4 matrixModel = m_registry->get<Transform>(e).getWorldTransform();
                renderInfo.material->render(m_engine, renderInfo.mesh.get(), matrixModel, matrixView, matrixProjection);

                if (glCheckError() != GL_NO_ERROR) {

                    auto* namePtr = m_registry->tryGet<en::Name>(e);
                    std::string name = namePtr ? namePtr->value : "unnamed";
                    std::cerr << "Error while rendering " << name << std::endl;
                }

                if (m_displayMeshDebugInfo) {
                    renderInfo.mesh->drawDebugInfo(matrixModel, matrixView, matrixProjection);
                }
            }
        }

        std::string debugInfo = std::string("FPS:") + std::to_string((int)m_engine->getFps()) + "\n";
        //std::cout << debugInfo;
        if ((m_engine->getWindow().getSettings().attributeFlags & sf::ContextSettings::Core) == 0) {
            m_debugHud->setDebugInfo(debugInfo);
            m_debugHud->draw();
        }
    }

    Actor RenderSystem::getMainCamera() {

        Entity entity = m_registry->with<Transform, Camera>().tryGetOne();
        return m_engine->actor(entity);
    }

    void GLAPIENTRY
    messageCallback(
        GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* userParam
    )
    {
        fprintf(
            stderr,
            "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            type, severity, message
        );
    }

    void enableDebug() {

        //glEnable(GL_DEBUG_OUTPUT);
        //glCheckError();
        //glDebugMessageCallback(messageCallback, 0);
    }
}
