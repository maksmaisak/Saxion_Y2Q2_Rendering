//
// Created by Maksym Maisak on 22/10/18.
//

#include "RenderSystem.h"
#include <iostream>
#include <tuple>
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

using namespace en;

void checkRenderingError(const Actor& actor) {

    if (glCheckError() == GL_NO_ERROR)
        return;

    auto* namePtr = actor.tryGet<en::Name>();
    std::string name = namePtr ? namePtr->value : "unnamed";
    std::cerr << "Error while rendering " << name << std::endl;
}

RenderSystem::RenderSystem(bool displayMeshDebugInfo) :
    m_displayMeshDebugInfo(displayMeshDebugInfo),
    m_directionalDepthShader(Resources<ShaderProgram>::get("depthDirectional")),
    m_positionalDepthShader (Resources<ShaderProgram>::get("depthPositional"))
{

    m_directionalDepthShaderAttribLocations.vertex = m_directionalDepthShader->getAttribLocation("vertex");
    m_directionalDepthShaderAttribLocations.normal = m_directionalDepthShader->getAttribLocation("normal");
    m_directionalDepthShaderAttribLocations.uv     = m_directionalDepthShader->getAttribLocation("uv");

    m_positionalDepthShaderAttribLocations.vertex = m_positionalDepthShader->getAttribLocation("vertex");
    m_positionalDepthShaderAttribLocations.normal = m_positionalDepthShader->getAttribLocation("normal");
    m_positionalDepthShaderAttribLocations.uv     = m_positionalDepthShader->getAttribLocation("uv");
}

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

    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

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
            renderInfo.material->render(renderInfo.mesh.get(), m_engine, &m_depthMaps, matrixModel, matrixView, matrixProjection);

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

    std::vector<Entity> directionalLights;
    std::vector<Entity> pointLights;

    for (Entity lightEntity : m_registry->with<Transform, Light>()) {

        auto& light = m_registry->get<Light>(lightEntity);
        auto& lightTransform = m_registry->get<Transform>(lightEntity);
        if (light.getKind() == Light::Kind::DIRECTIONAL) {
            updateDepthMapDirectionalLight(light, lightTransform);
            directionalLights.push_back(lightEntity);
        } else {
            //updateDepthMapPositionalLight(light, lightTransform);
            pointLights.push_back(lightEntity);
        }

        glCheckError();
    }

    updateDepthMapsDirectionalLights(directionalLights);
    updateDepthMapsPositionalLights(pointLights);

    auto size = m_engine->getWindow().getSize();
    glViewport(0, 0, size.x, size.y);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glCheckError();
}

glm::mat4 getDirectionalLightspaceTransform(const Light& light, const Transform& lightTransform) {

    glm::mat4 lightProjectionMatrix = light.getProjectionMatrix();
    glm::mat4 lightViewMatrix = light.getViewMatrix(lightTransform);
    return lightProjectionMatrix * lightViewMatrix;
}

void RenderSystem::updateDepthMapDirectionalLight(const Light& light, const Transform& lightTransform) {

    m_directionalDepthShader->use();
    m_directionalDepthShader->setUniformValue("matrixPV", getDirectionalLightspaceTransform(light, lightTransform));

    glViewport(0, 0, Light::DepthMapResolution.x, Light::DepthMapResolution.y);
    glBindFramebuffer(GL_FRAMEBUFFER, light.getFramebufferId());
    glClear(GL_DEPTH_BUFFER_BIT);
    for (Entity e : m_registry->with<Transform, RenderInfo>()) {

        Mesh* mesh = m_registry->get<RenderInfo>(e).mesh.get();
        if (!mesh)
            continue;
        const glm::mat4& modelTransform = m_registry->get<Transform>(e).getWorldTransform();
        m_directionalDepthShader->setUniformValue("matrixModel", modelTransform);
        mesh->streamToOpenGL(
            m_directionalDepthShaderAttribLocations.vertex,
            m_directionalDepthShaderAttribLocations.normal,
            m_directionalDepthShaderAttribLocations.uv
        );

        checkRenderingError(m_engine->actor(e));
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

std::tuple<float, glm::vec3, std::array<glm::mat4, 6>> getPointLightUniforms(const Light& light, const Transform& lightTransform) {

    float nearPlaneDistance = 1.f;
    float farPlaneDistance = 40.f;
    glm::mat4 lightProjectionMatrix = glm::perspective(
        glm::radians(90.f),
        (float)DepthMaps::CUBEMAP_RESOLUTION.x / (float)DepthMaps::CUBEMAP_RESOLUTION.y,
        nearPlaneDistance,
        farPlaneDistance
    );

    glm::vec3 lightPosition = lightTransform.getWorldPosition();

    return {
        farPlaneDistance,
        lightPosition,
        {
            lightProjectionMatrix * glm::lookAt(lightPosition, lightPosition + glm::vec3( 1.0f, 0.0f, 0.0f), glm::vec3(0.0f,-1.0f, 0.0f)),
            lightProjectionMatrix * glm::lookAt(lightPosition, lightPosition + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f,-1.0f, 0.0f)),
            lightProjectionMatrix * glm::lookAt(lightPosition, lightPosition + glm::vec3( 0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
            lightProjectionMatrix * glm::lookAt(lightPosition, lightPosition + glm::vec3( 0.0f,-1.0f, 0.0f), glm::vec3(0.0f, 0.0f,-1.0f)),
            lightProjectionMatrix * glm::lookAt(lightPosition, lightPosition + glm::vec3( 0.0f, 0.0f, 1.0f), glm::vec3(0.0f,-1.0f, 0.0f)),
            lightProjectionMatrix * glm::lookAt(lightPosition, lightPosition + glm::vec3( 0.0f, 0.0f,-1.0f), glm::vec3(0.0f,-1.0f, 0.0f))
        }
    };
}

void RenderSystem::updateDepthMapsDirectionalLights(const std::vector<Entity>& directionalLights) {

}

void RenderSystem::updateDepthMapsPositionalLights(const std::vector<Entity>& pointLights) {

    glViewport(0, 0, DepthMaps::CUBEMAP_RESOLUTION.x, DepthMaps::CUBEMAP_RESOLUTION.y);
    glBindFramebuffer(GL_FRAMEBUFFER, m_depthMaps.getCubemapsFramebufferId());
    glClear(GL_DEPTH_BUFFER_BIT);

    m_positionalDepthShader->use();

    int maxNumCubemaps = 10;
    int i = 0;
    for (Entity e : pointLights) {

        auto& light = m_registry->get<Light>(e);
        auto& tf = m_registry->get<Transform>(e);
        auto [farPlaneDistance, lightPosition, pvMatrices] = getPointLightUniforms(light, tf);

        for (unsigned int face = 0; face < 6; ++face)
            m_positionalDepthShader->setUniformValue("matrixPV[" + std::to_string(i * 6 + face) + "]", pvMatrices[face]);
        std::string prefix = "lights[" + std::to_string(i) + "].";
        m_positionalDepthShader->setUniformValue(prefix + "position", lightPosition);
        m_positionalDepthShader->setUniformValue(prefix + "farPlaneDistance", farPlaneDistance);

        if (++i >= maxNumCubemaps)
            break;
    }
    m_positionalDepthShader->setUniformValue("numLights", i);

    for (Entity e : m_registry->with<Transform, RenderInfo>()) {

        Mesh* mesh = m_registry->get<RenderInfo>(e).mesh.get();
        if (!mesh)
            continue;

        const glm::mat4& modelTransform = m_registry->get<Transform>(e).getWorldTransform();
        m_positionalDepthShader->setUniformValue("matrixModel", modelTransform);
        glCheckError();
        mesh->streamToOpenGL(
            m_positionalDepthShaderAttribLocations.vertex,
            m_positionalDepthShaderAttribLocations.normal,
            m_positionalDepthShaderAttribLocations.uv
        );
        glCheckError();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glCheckError();
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

    glEnable(GL_DEBUG_OUTPUT);
    glCheckError();
    glDebugMessageCallback(messageCallback, 0);
}
