//
// Created by Maksym Maisak on 22/10/18.
//

#include "RenderSystem.h"
#include <iostream>
#include <tuple>
#include <string>
#include <sstream>
#include <cmath>
#include "components/RenderInfo.h"
#include "components/Transform.h"
#include "components/Camera.h"
#include "components/Name.h"
#include "components/Sprite.h"
#include "components/Text.h"
#include "GLHelpers.h"
#include "Font.h"
#include "GameTime.h"
#include "Resources.h"
#include "Material.h"
#include "Exception.h"
#include "UIRect.h"
#include "AbstractMaterial.hpp"

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
    m_depthMaps(4, {1024, 1024}, 10, {64, 64}),
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

    //glClearColor(0, 0, 0, 1);
    const glm::vec3 color = glm::pow(glm::vec3(62.f / 255, 84.f / 255, 92.f / 255), glm::vec3(2.2f));
    glClearColor(color.x, color.y, color.z, 1.f);

    // Convert output from fragment shaders from linear to sRGB
    glEnable(GL_FRAMEBUFFER_SRGB);

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    m_debugHud = std::make_unique<DebugHud>(&m_engine->getWindow());

    auto& lua = m_engine->getLuaState();
    lua_getglobal(lua, "Config");
    auto popConfig = lua::PopperOnDestruct(lua);
    m_referenceResolution = lua.tryGetField<glm::vec2>("referenceResolution").value_or(glm::vec2(1920, 1080));
}

namespace {

    glm::mat4 getProjectionMatrix(Engine& engine, Camera& camera) {

        auto size = engine.getWindow().getSize();
        float aspectRatio = (float) size.x / size.y;

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
            (float) size.x / size.y,
            camera.nearPlaneDistance,
            camera.farPlaneDistance
        );
    }
}

void RenderSystem::draw() {

    if (glCheckError() != GL_NO_ERROR) {
        std::cerr << "Uncaught openGL error(s) before rendering." << std::endl;
    }

    updateBatches();

    updateDepthMaps();
    renderEntities();
    renderUI();
    renderDebug();
}

namespace {

    bool compareRenderInfo(const RenderInfo& a, const RenderInfo& b) {

        if (a.isBatchingStatic < b.isBatchingStatic) return true;
        if (a.isBatchingStatic > b.isBatchingStatic) return false;

        if (a.material < b.material) return true;
        if (a.material > b.material) return false;

        return a.model < b.model;
    }
}

void RenderSystem::updateBatches() {

    for (Entity e : m_registry->with<Transform, RenderInfo>()) {

        auto& renderInfo = m_registry->get<RenderInfo>(e);
        if (renderInfo.isInBatch || !renderInfo.isBatchingStatic)
            continue;

        if (!renderInfo.material || !renderInfo.model)
            continue;

        auto it = m_batches.find(renderInfo.material);
        if (it == m_batches.end()) {
            std::tie(it, std::ignore) = m_batches.emplace(std::make_pair(renderInfo.material, Mesh()));
        }

        const auto& worldMatrix = m_registry->get<Transform>(e).getWorldTransform();
        for (auto& mesh : renderInfo.model->getMeshes())
            it->second.add(mesh, worldMatrix);
        renderInfo.isInBatch = true;
    }

    for (auto& [material, batch] : m_batches) {
        //batch.removeDestroyed();
        batch.updateBuffers();
    }
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

    // Draw batches.
    for (const auto& [material, mesh] : m_batches) {
        material->render(&mesh, m_engine, &m_depthMaps, glm::mat4(1), matrixView, matrixProjection);
    }

    int numBatched = 0;
    for (Entity e : m_registry->with<Transform, RenderInfo>()) {

        auto& renderInfo = m_registry->get<RenderInfo>(e);
        if (renderInfo.isInBatch) {
            numBatched += 1;
            continue;
        }

        if (!renderInfo.isEnabled || !renderInfo.material || !renderInfo.model)
            continue;

        const glm::mat4& matrixModel = m_registry->get<Transform>(e).getWorldTransform();
        for (const Mesh& mesh : renderInfo.model->getMeshes()) {
            renderInfo.material->render(&mesh,
                m_engine,
                &m_depthMaps,
                matrixModel,
                matrixView,
                matrixProjection
            );
        }

        checkRenderingError(m_engine->actor(e));
    }
    //std::cout << "Draw calls saved by batching: " << numBatched - m_batches.size() << '\n';
}

void updateUIRect(Engine& engine, EntityRegistry& registry, Entity e, const glm::vec2& parentSize, const glm::vec2& parentPivot, float scaleFactor) {

    auto& rect = registry.get<UIRect>(e);
    auto* tf = registry.tryGet<Transform>(e);
    if (!tf)
        return;

    const glm::vec2 parentMinToLocalMin = parentSize * rect.anchorMin + rect.offsetMin * scaleFactor;
    const glm::vec2 parentMinToLocalMax = parentSize * rect.anchorMax + rect.offsetMax * scaleFactor;
    rect.computedSize = parentMinToLocalMax - parentMinToLocalMin;

    const glm::vec2 parentMinToLocalPivot  = glm::lerp(parentMinToLocalMin, parentMinToLocalMax, rect.pivot);
    const glm::vec2 parentPivotToParentMin = -parentSize * parentPivot;
    const glm::vec2 parentPivotToLocalPivot = parentPivotToParentMin + parentMinToLocalPivot;
    tf->setLocalPosition(glm::vec3(parentPivotToLocalPivot, tf->getLocalPosition().z));

    for (Entity child : tf->getChildren())
        updateUIRect(engine, registry, child, rect.computedSize, rect.pivot, scaleFactor);
}

void RenderSystem::renderUI() {

    glDisable(GL_DEPTH_TEST);

    for (Entity e : m_registry->with<Transform, UIRect>())
        if (!m_registry->get<Transform>(e).getParent())
            updateUIRect(*m_engine, *m_registry, e, getWindowSize(), {0, 0}, getUIScaleFactor());

    for (Entity e : m_registry->with<Transform, UIRect>())
        if (!m_registry->get<Transform>(e).getParent())
            renderUIRect(e, m_registry->get<UIRect>(e));

    glEnable(GL_DEPTH_TEST);
}

void RenderSystem::renderUIRect(Entity e, UIRect& rect) {

    if (!rect.isEnabled)
        return;

    auto* tf = m_registry->tryGet<Transform>(e);
    if (!tf)
        return;

    const glm::vec2 windowSize = getWindowSize();
    const glm::mat4 matrixProjection = glm::ortho(0.f, windowSize.x, 0.f, windowSize.y);

    auto* sprite = m_registry->tryGet<Sprite>(e);
    if (sprite && sprite->isEnabled && sprite->material) {

        const glm::mat4& transform = tf->getWorldTransform();
        const glm::vec2 localMin = -rect.computedSize * rect.pivot;
        const glm::vec2 localMax =  rect.computedSize * (1.f - rect.pivot);
        const glm::vec3 corners[] = {
            transform * glm::vec4(localMin              , 0, 1),
            transform * glm::vec4(localMin.x, localMax.y, 0, 1),
            transform * glm::vec4(localMax.x, localMin.y, 0, 1),
            transform * glm::vec4(localMax              , 0, 1)
        };
        const std::vector<Vertex> vertices = {
            {corners[1], {0, 1}},
            {corners[0], {0, 0}},
            {corners[2], {1, 0}},

            {corners[1], {0, 1}},
            {corners[2], {1, 0}},
            {corners[3], {1, 1}},
        };

        sprite->material->use(m_engine, &m_depthMaps, glm::mat4(1), glm::mat4(1), matrixProjection);
        m_vertexRenderer.renderVertices(vertices);
    }

    auto* text = m_registry->tryGet<Text>(e);
    if (text && text->getMaterial()) {

        const std::vector<Vertex>& vertices = text->getVertices();

        const glm::vec2 boundsCenter = (text->getBoundsMin() + text->getBoundsMax()) * 0.5f;
        const glm::vec2 offset = rect.computedSize * (0.5f - rect.pivot) - boundsCenter;

        // Scale the bounds by the scale factor and bring them to the rect's position.
        glm::mat4 matrix = glm::translate(glm::vec3(-boundsCenter.x, -boundsCenter.y, 0.f));
        matrix = glm::scale(glm::vec3(getUIScaleFactor())) * matrix;
        matrix = glm::translate(glm::vec3(boundsCenter.x, boundsCenter.y, 0.f)) * matrix;
        matrix = glm::translate(glm::vec3(offset.x, offset.y, 0.f)) * matrix;
        matrix = tf->getWorldTransform() * matrix;

        text->getMaterial()->use(m_engine, &m_depthMaps, glm::mat4(1), glm::mat4(1), matrixProjection * matrix);
        m_vertexRenderer.renderVertices(vertices);
    }

    for (Entity child : tf->getChildren())
        if (auto* childRect = m_registry->tryGet<UIRect>(child))
            renderUIRect(child, *childRect);
}

void RenderSystem::renderDebug() {

    glDisable(GL_DEPTH_TEST);

    std::stringstream s;
    s << "fps: " << glm::iround(m_engine->getFps()) << " frame: " << m_engine->getFrameTimeMicroseconds() / 1000.0 << "ms";
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

namespace {

    glm::mat4 getDirectionalLightspaceTransform(const Light& light, const Transform& lightTransform) {

        glm::mat4 lightProjectionMatrix = glm::ortho(
            -20.f, 20.f,
            -20.f, 20.f,
            light.nearPlaneDistance, light.farPlaneDistance
        );

        glm::mat4 lightViewMatrix = glm::lookAt(-lightTransform.getForward() * 10, {0, 0, 0}, {0, 1, 0});

        return lightProjectionMatrix * lightViewMatrix;
    }
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

    m_directionalDepthShader->setUniformValue("matrixModel", glm::mat4(1));
    for (const auto& [material, mesh] : m_batches) {
        mesh.render(0, -1, -1);
    }

    for (Entity e : m_registry->with<Transform, RenderInfo>()) {

        auto& renderInfo = m_registry->get<RenderInfo>(e);
        if (renderInfo.isInBatch || !renderInfo.isEnabled || !renderInfo.model)
            continue;

        const glm::mat4& modelTransform = m_registry->get<Transform>(e).getWorldTransform();
        m_directionalDepthShader->setUniformValue("matrixModel", modelTransform);
        for (const Mesh& mesh : renderInfo.model->getMeshes())
            mesh.render(0, -1, -1);

        checkRenderingError(m_engine->actor(e));
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

namespace {

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

    m_positionalDepthShader->setUniformValue("matrixModel", glm::mat4(1));
    for (const auto& [material, mesh] : m_batches) {
        mesh.render(0, -1, -1);
    }

    for (Entity e : m_registry->with<Transform, RenderInfo>()) {

        auto& renderInfo = m_registry->get<RenderInfo>(e);
        if (renderInfo.isInBatch || !renderInfo.isEnabled || !renderInfo.model)
            continue;

        const glm::mat4& modelTransform = m_registry->get<Transform>(e).getWorldTransform();
        m_positionalDepthShader->setUniformValue("matrixModel", modelTransform);
        for (const Mesh& mesh : renderInfo.model->getMeshes())
            mesh.render(0, -1, -1);
        glCheckError();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glCheckError();
}

glm::vec2 RenderSystem::getWindowSize() {

    sf::Vector2u windowSizeSf = m_engine->getWindow().getSize();
    return glm::vec2(windowSizeSf.x, windowSizeSf.y);
}

float RenderSystem::getUIScaleFactor() {

    const glm::vec2 windowSize = getWindowSize();
    return std::sqrt((windowSize.x / m_referenceResolution.x) * (windowSize.y / m_referenceResolution.y));
}

namespace {

    void GLAPIENTRY
    messageCallback(
        GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* userParam
    ) {

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
}
