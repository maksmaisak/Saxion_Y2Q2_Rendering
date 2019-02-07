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
#include "Font.h"
#include "GameTime.h"
#include "Resources.h"
#include "Material.h"
#include "Exception.h"

namespace en {

    void checkRenderingError() {
        if (glCheckError() == GL_NO_ERROR)
            return;

        std::cout << "";
    }

    void checkRenderingError(const Actor& actor) {

        if (glCheckError() == GL_NO_ERROR)
            return;

        auto* namePtr = actor.tryGet<en::Name>();
        std::string name = namePtr ? namePtr->value : "unnamed";
        std::cerr << "Error while rendering " << name << std::endl;
    }

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

        // Convert ouput from fragment shaders from linear to sRGB
        glEnable(GL_FRAMEBUFFER_SRGB);

        // Disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        m_debugHud = std::make_unique<DebugHud>(&m_engine->getWindow());
    }

    void RenderSystem::draw() {

        if (glCheckError() != GL_NO_ERROR) {
            std::cerr << "Uncaught openGL error(s) before rendering." << std::endl;
        }

        updateDepthMaps();

        Actor mainCamera = getMainCamera();
        if (mainCamera) {

            glm::mat4 matrixView = glm::inverse(mainCamera.get<Transform>().getWorldTransform());
            glm::mat4 matrixProjection = mainCamera.get<Camera>().projectionMatrix;

            for (Entity e : m_registry->with<Transform, RenderInfo>()) {

                auto& renderInfo = m_registry->get<RenderInfo>(e);
                if (!renderInfo.material || !renderInfo.mesh)
                    continue;

                const glm::mat4& matrixModel = m_registry->get<Transform>(e).getWorldTransform();
                renderInfo.material->render(m_engine, renderInfo.mesh.get(), matrixModel, matrixView, matrixProjection);

                checkRenderingError(m_engine->actor(e));

                if (m_displayMeshDebugInfo) {
                    renderInfo.mesh->drawDebugInfo(matrixModel, matrixView, matrixProjection);
                }
            }
        }

        std::string debugInfo = std::string("FPS:") + std::to_string((int)m_engine->getFps());
        auto font = Resources<Font>::get(config::FONT_PATH + "arial.ttf");
        auto windowSize = m_engine->getWindow().getSize();
        font->render(debugInfo, {0.f, 0.f}, 1.f, glm::ortho(0.f, (float)windowSize.x, 0.f, (float)windowSize.y));
    }

    Actor RenderSystem::getMainCamera() {

        Entity entity = m_registry->with<Transform, Camera>().tryGetOne();
        return m_engine->actor(entity);
    }

    void RenderSystem::updateDepthMaps() {

        auto material = Resources<Material>::get("depth");

        checkRenderingError();
        for (Entity lightEntity : m_registry->with<Transform, Light>()) {

            auto& light = m_registry->get<Light>(lightEntity);
            if (light.getKind() != Light::Kind::DIRECTIONAL)
                continue;

            auto& lightTransform = m_registry->get<Transform>(lightEntity);
            glm::mat4 lightProjectionMatrix = glm::ortho(-10.0, 10.0, -10.0, 10.0);
            glm::mat4 lightViewMatrix = glm::lookAt(-lightTransform.getForward() * 10, {0, 0, 0}, {0, 1, 0});

            checkRenderingError();
            glViewport(0, 0, Light::DepthMapResolution.x, Light::DepthMapResolution.y);
            checkRenderingError();
            glBindFramebuffer(GL_FRAMEBUFFER, light.getFramebufferId());
            checkRenderingError();
            {
                checkRenderingError();
                glClear(GL_DEPTH_BUFFER_BIT);
                checkRenderingError();
                for (Entity e : m_registry->with<Transform, RenderInfo>()) {

                    Mesh* mesh = m_registry->get<RenderInfo>(e).mesh.get();
                    const glm::mat4& modelTransform = m_registry->get<Transform>(e).getWorldTransform();
                    material->render(m_engine, mesh, modelTransform, lightViewMatrix, lightProjectionMatrix);

                    checkRenderingError(m_engine->actor(e));
                }
            }
            checkRenderingError();
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            checkRenderingError();
        }
        checkRenderingError();

        auto size = m_engine->getWindow().getSize();
        glViewport(0, 0, size.x, size.y);
        checkRenderingError();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        checkRenderingError();
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
