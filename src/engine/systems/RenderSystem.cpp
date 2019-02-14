//
// Created by Maksym Maisak on 22/10/18.
//

#include "RenderSystem.h"
#include <iostream>
#include <tuple>
#include <string>
#include <sstream>
#include "components/RenderInfo.h"
#include "components/Transform.h"
#include "components/Camera.h"
#include "components/Name.h"
#include "components/Sprite.h"
#include "GLHelpers.h"
#include "Font.h"
#include "GameTime.h"
#include "Resources.h"
#include "Material.h"
#include "Exception.h"
#include "UIRect.h"

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
    m_positionalDepthShader (Resources<ShaderProgram>::get("depthPositional")),
    m_depthMaps(4, {1024, 1024}, 10, {512, 512}),
    m_vertexRenderer(4096)
{}

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

glm::mat4 getProjectionMatrix(Engine& engine, Camera& camera) {

    auto size = engine.getWindow().getSize();
    float aspectRatio = (float)size.x / size.y;

    if (camera.isOrthographic) {

        glm::vec2 halfSize = {
            camera.orthographicHalfSize * aspectRatio,
            camera.orthographicHalfSize
        };

        return glm::ortho(
            -halfSize.x, halfSize.x,
            -halfSize.y, halfSize.y,
            camera.nearPlaneDistance, camera.farPlaneDistance
        );
    }

    return glm::perspective(
        glm::radians(camera.fov),
        (float)size.x / size.y,
        camera.nearPlaneDistance,
        camera.farPlaneDistance
    );
}

void RenderSystem::draw() {

    if (glCheckError() != GL_NO_ERROR) {
        std::cerr << "Uncaught openGL error(s) before rendering." << std::endl;
    }

    updateDepthMaps();
    renderEntities();
    renderUI();
    renderDebug();
}

void RenderSystem::updateDepthMaps() {

    std::vector<Entity> directionalLights;
    std::vector<Entity> pointLights;

    for (Entity lightEntity : m_registry->with<Transform, Light>()) {

        auto& light = m_registry->get<Light>(lightEntity);
        if (light.kind == Light::Kind::DIRECTIONAL)
            directionalLights.push_back(lightEntity);
        else
            pointLights.push_back(lightEntity);
    }

    updateDepthMapsDirectionalLights(directionalLights);
    updateDepthMapsPositionalLights(pointLights);

    auto size = m_engine->getWindow().getSize();
    glViewport(0, 0, size.x, size.y);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glCheckError();
}

void RenderSystem::renderEntities() {

    Actor mainCamera = getMainCamera();
    if (!mainCamera)
        return;

    glm::mat4 matrixView = glm::inverse(mainCamera.get<Transform>().getWorldTransform());
    glm::mat4 matrixProjection = getProjectionMatrix(*m_engine, mainCamera.get<Camera>());

    for (Entity e : m_registry->with<Transform, RenderInfo>()) {

        auto& renderInfo = m_registry->get<RenderInfo>(e);
        if (!renderInfo.isEnabled || !renderInfo.material || !renderInfo.mesh)
            continue;

        const glm::mat4& matrixModel = m_registry->get<Transform>(e).getWorldTransform();
        renderInfo.material->render(renderInfo.mesh.get(), m_engine, &m_depthMaps, matrixModel, matrixView, matrixProjection);

        checkRenderingError(m_engine->actor(e));

        if (m_displayMeshDebugInfo) {
            renderInfo.mesh->drawDebugInfo(matrixModel, matrixView, matrixProjection);
        }
    }
}

std::tuple<glm::vec2, glm::vec2> getBounds(UIRect& rect, const glm::vec2& parentMin, const glm::vec2& parentMax) {

    const glm::vec2 min = glm::lerp(parentMin, parentMax, rect.anchorMin) + rect.offsetMin;
    const glm::vec2 max = glm::lerp(parentMin, parentMax, rect.anchorMax) + rect.offsetMax;
    return {min, max};
}

void RenderSystem::renderUI() {

    glDisable(GL_DEPTH_TEST);

    sf::Vector2u windowSizeSf = m_engine->getWindow().getSize();
    auto windowSize = glm::vec2(windowSizeSf.x, windowSizeSf.y);
    glm::mat4 matrixProjection = glm::ortho(0.f, windowSize.x, 0.f, windowSize.y);
    //glm::mat4 matrixProjection = glm::ortho(0.f, 1.f, 0.f, 1.f);

    glm::vec2 parentMin = {0, 0};
    glm::vec2 parentMax = windowSize;

    for (Entity e : m_registry->with<Transform, UIRect>()) {

        auto& tf = m_registry->get<Transform>(e);
        if (tf.getParent())
            continue;

        auto& rect = m_registry->get<UIRect>(e);
        if (!rect.isEnabled)
            continue;

        auto[min, max] = getBounds(rect, parentMin, parentMax);
        renderUIRect(e, min, max);
        renderUIRects(tf.getChildren(), min, max);
    }

    glEnable(GL_DEPTH_TEST);
}

void RenderSystem::renderUIRects(const std::vector<Entity>& children, glm::vec2 parentMin, glm::vec2 parentMax) {

    for (Entity e : children) {

        auto* rect = m_registry->tryGet<UIRect>(e);
        if (!rect || !rect->isEnabled)
            continue;

        auto[min, max] = getBounds(*rect, parentMin, parentMax);
        renderUIRect(e, min, max);
        if (auto* tf = m_registry->tryGet<Transform>(e)) {
            renderUIRects(tf->getChildren(), min, max);
        }
    }
}

void RenderSystem::renderUIRect(Entity entity, glm::vec2 min, glm::vec2 max) {

    auto* sprite = m_registry->tryGet<Sprite>(entity);
    if (sprite && sprite->isEnabled && sprite->material) {

        std::vector<Vertex> vertices = {
            {{min.x, max.y, 0}, {0, 1}},
            {{min.x, min.y, 0}, {0, 0}},
            {{max.x, min.y, 0}, {1, 0}},

            {{min.x, max.y, 0}, {0, 1}},
            {{max.x, min.y, 0}, {1, 0}},
            {{max.x, max.y, 0}, {1, 1}},
        };

        glm::vec2 size = getWindowSize();
        sprite->material->use(m_engine, &m_depthMaps, glm::mat4(1), glm::mat4(1), glm::ortho(0.f, size.x, 0.f, size.y));
        m_vertexRenderer.renderVertices(vertices);
    }
}

void RenderSystem::renderDebug() {

    glDisable(GL_DEPTH_TEST);

    std::stringstream s;
    s << "fps:" << glm::iround(m_engine->getFps()) << " frame: " << m_engine->getFrameTimeMicroseconds() / 1000.0 << "ms";
    std::string debugInfo = s.str();

    auto font = Resources<Font>::get(config::FONT_PATH + "arial.ttf");
    auto windowSize = m_engine->getWindow().getSize();
    font->render(debugInfo, {0.f, 0.f}, 0.5f, glm::ortho(0.f, (float)windowSize.x, 0.f, (float)windowSize.y));

    glEnable(GL_DEPTH_TEST);
}

Actor RenderSystem::getMainCamera() {

    Entity entity = m_registry->with<Transform, Camera>().tryGetOne();
    return m_engine->actor(entity);
}

glm::mat4 getDirectionalLightspaceTransform(const Light& light, const Transform& lightTransform) {

    glm::mat4 lightProjectionMatrix = glm::ortho(
        -20.f, 20.f,
        -20.f, 20.f,
        light.nearPlaneDistance, light.farPlaneDistance
    );

    glm::mat4 lightViewMatrix = glm::lookAt(lightTransform.getForward() * 10, {0, 0, 0}, {0, 1, 0});

    return lightProjectionMatrix * lightViewMatrix;
}

void RenderSystem::updateDepthMapsDirectionalLights(const std::vector<Entity>& directionalLights) {

    glViewport(0, 0, m_depthMaps.getDirectionalMapResolution().x, m_depthMaps.getDirectionalMapResolution().y);
    glBindFramebuffer(GL_FRAMEBUFFER, m_depthMaps.getDirectionalMapsFramebufferId());
    glClear(GL_DEPTH_BUFFER_BIT);

    m_directionalDepthShader->use();
    int i = 0;
    for (Entity e : directionalLights) {

        if (i >= m_depthMaps.getMaxNumDirectionalLights())
            break;

        auto& light = m_registry->get<Light>(e);
        auto& tf = m_registry->get<Transform>(e);
        light.matrixPV = getDirectionalLightspaceTransform(light, tf);
        m_directionalDepthShader->setUniformValue("matrixPV[" + std::to_string(i) + "]", light.matrixPV);

        i += 1;
    }
    m_directionalDepthShader->setUniformValue("numLights", i);

    for (Entity e : m_registry->with<Transform, RenderInfo>()) {

        Mesh* mesh = m_registry->get<RenderInfo>(e).mesh.get();
        if (!mesh)
            continue;
        const glm::mat4& modelTransform = m_registry->get<Transform>(e).getWorldTransform();
        m_directionalDepthShader->setUniformValue("matrixModel", modelTransform);
        mesh->streamToOpenGL(0, -1, -1);

        checkRenderingError(m_engine->actor(e));
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

std::tuple<float, glm::vec3, std::array<glm::mat4, 6>> getPointLightUniforms(const DepthMaps& depthMaps, const Light& light, const Transform& lightTransform) {

    float nearPlaneDistance = light.nearPlaneDistance;
    float farPlaneDistance  = light.farPlaneDistance;
    glm::mat4 lightProjectionMatrix = glm::perspective(
        glm::radians(90.f),
        (float)depthMaps.getCubemapResolution().x / (float)depthMaps.getCubemapResolution().y,
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

void RenderSystem::updateDepthMapsPositionalLights(const std::vector<Entity>& pointLights) {

    glViewport(0, 0, m_depthMaps.getCubemapResolution().x, m_depthMaps.getCubemapResolution().y);
    glBindFramebuffer(GL_FRAMEBUFFER, m_depthMaps.getCubemapsFramebufferId());
    glClear(GL_DEPTH_BUFFER_BIT);

    m_positionalDepthShader->use();

    int i = 0;
    for (Entity e : pointLights) {

        auto& light = m_registry->get<Light>(e);
        auto& tf = m_registry->get<Transform>(e);
        auto [farPlaneDistance, lightPosition, pvMatrices] = getPointLightUniforms(m_depthMaps, light, tf);

        for (unsigned int face = 0; face < 6; ++face)
            m_positionalDepthShader->setUniformValue("matrixPV[" + std::to_string(i * 6 + face) + "]", pvMatrices[face]);
        std::string prefix = "lights[" + std::to_string(i) + "].";
        m_positionalDepthShader->setUniformValue(prefix + "position", lightPosition);
        m_positionalDepthShader->setUniformValue(prefix + "farPlaneDistance", farPlaneDistance);

        if (++i >= m_depthMaps.getMaxNumPositionalLights())
            break;
    }
    m_positionalDepthShader->setUniformValue("numLights", i);

    for (Entity e : m_registry->with<Transform, RenderInfo>()) {

        Mesh* mesh = m_registry->get<RenderInfo>(e).mesh.get();
        if (!mesh)
            continue;

        const glm::mat4& modelTransform = m_registry->get<Transform>(e).getWorldTransform();
        m_positionalDepthShader->setUniformValue("matrixModel", modelTransform);
        mesh->streamToOpenGL(0, -1, -1);
        glCheckError();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glCheckError();
}

glm::vec2 RenderSystem::getWindowSize() {

    sf::Vector2u windowSizeSf = m_engine->getWindow().getSize();
    return glm::vec2(windowSizeSf.x, windowSizeSf.y);
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
