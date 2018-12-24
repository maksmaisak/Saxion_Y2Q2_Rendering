//
// Created by Maksym Maisak on 22/10/18.
//

#include "RenderSystem.h"
#include "components/DrawInfo.h"
#include "components/RenderInfo.h"
#include "components/Transformable.h"
#include "components/Camera.h"

namespace en {

    RenderSystem::RenderSystem(bool displayMeshDebugInfo) :
        m_displayMeshDebugInfo(displayMeshDebugInfo) {}

    void RenderSystem::start() {

        glEnable(GL_DEPTH_TEST);

        // Counterclockwise vertex order
        glFrontFace(GL_CCW);

        // Enable back face culling
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        //set the default blend mode aka dark magic:
        //https://www.opengl.org/sdk/docs/man/html/glBlendFunc.xhtml
        //https://www.opengl.org/wiki/Blending
        //http://www.informit.com/articles/article.aspx?p=1616796&seqNum=5
        //http://www.andersriggelsen.dk/glblendfunc.php
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glClearColor((float)0x2d / 0xff, (float)0x6b / 0xff, (float)0xce / 0xff, 1.0f);

        m_debugHud = std::make_unique<DebugHud>(&m_engine->getWindow());
    }

    void RenderSystem::draw() {

        Actor mainCamera = getMainCamera();
        glm::mat4 matrixView = glm::inverse(mainCamera.get<Transformable>().getWorldTransform());
        glm::mat4 matrixProjection = mainCamera.get<Camera>().projectionMatrix;

        for (Entity e : m_registry->with<Transformable, RenderInfo>()) {

            auto& renderInfo = m_registry->get<RenderInfo>(e);
            if (!renderInfo.material || !renderInfo.mesh) continue;

            glm::mat4 matrixModel = m_registry->get<Transformable>(e).getWorldTransform();
            renderInfo.material->render(m_engine, renderInfo.mesh.get(), matrixModel, matrixView, matrixProjection);

            if (m_displayMeshDebugInfo) {
                renderInfo.mesh->drawDebugInfo(matrixModel, matrixView, matrixProjection);
            }
        }

        m_debugHud->draw();
    }

    Actor RenderSystem::getMainCamera() {

        Entity entity = *m_registry->with<Transformable, Camera>().begin();
        return m_engine->actor(entity);
    }
}
