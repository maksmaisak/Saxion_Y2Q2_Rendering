//
// Created by Maksym Maisak on 2019-01-09.
//

#include <cassert>
#include <iostream>
#include <utility>
#include "engine/components/Transform.h"
#include "engine/components/Light.h"
#include "Material.h"
#include "Resources.h"
#include "Mesh.hpp"
#include "GLHelpers.h"
#include "GLSetUniform.h"
#include "TupleUtils.h"
#include "GameTime.h"

using namespace en;

Material::Material(const std::string& shaderFilename) :
    Material(Resources<ShaderProgram>::get(shaderFilename)) {}

Material::Material(std::shared_ptr<ShaderProgram> shader) : m_shader(std::move(shader)) {

    assert(m_shader);

    m_builtinUniformLocations = cacheBuiltinUniformLocations();
    m_attributeLocations = cacheAttributeLocations();
    detectAllUniforms();
}

void Material::render(Engine* engine, Mesh* mesh,
    const glm::mat4& modelMatrix,
    const glm::mat4& viewMatrix,
    const glm::mat4& perspectiveMatrix
) {
    m_shader->use();

    setBuiltinUniforms(engine, modelMatrix, viewMatrix, perspectiveMatrix);
    setCustomUniforms();

    const auto& a = m_attributeLocations;
    mesh->streamToOpenGL(a.vertex, a.normal, a.uv);
}

inline bool valid(GLint location) {return location != -1;}

void Material::setBuiltinUniforms(
    Engine* engine,
    const glm::mat4& modelMatrix,
    const glm::mat4& viewMatrix,
    const glm::mat4& perspectiveMatrix
) {
    const auto& u = m_builtinUniformLocations;

    // glUniform functions do nothing if location is -1, so checks are only necessary for avoiding calculations.

    gl::setUniform(u.model     , modelMatrix     );
    gl::setUniform(u.view      , viewMatrix      );
    gl::setUniform(u.projection, perspectiveMatrix);

    if (valid(u.pvm))
        gl::setUniform(u.pvm, perspectiveMatrix * viewMatrix * modelMatrix);

    if (valid(u.time))
        gl::setUniform(u.time, GameTime::now().asSeconds());

    if (valid(u.viewPosition))
        gl::setUniform(u.viewPosition, glm::vec3(glm::inverse(viewMatrix)[3]));

    auto& registry = engine->getRegistry();

    // Add lights
    int numPointLights = 0;
    int numDirectionalLights = 0;
    int numSpotLights = 0;
    for (Entity e : registry.with<Transform, Light>()) {

        // TODO sort lights by proximity, pick the closest ones.

        auto& light = registry.get<Light>(e);
        auto& tf = registry.get<Transform>(e);

        switch (light.kind) {
            case Light::Kind::POINT:
                if (numPointLights >= m_numSupportedPointLights)
                    break;
                setUniformsPointLight(u.pointLights[numPointLights], light, tf);
                numPointLights += 1;
                break;
            case Light::Kind::DIRECTIONAL:
                if (numDirectionalLights >= m_numSupportedDirectionalLights)
                    break;
                setUniformDirectionalLight(u.directionalLights[numDirectionalLights], light, tf);
                numDirectionalLights += 1;
                break;
            case Light::Kind::SPOT:
                if (numSpotLights >= m_numSupportedSpotLights)
                    break;
                setUniformSpotLight(u.spotLights[numSpotLights], light, tf);
                numSpotLights += 1;
                break;
            default:
                break;
        }
    }
    gl::setUniform(u.numPointLights, numPointLights);
    gl::setUniform(u.numDirectionalLights, numDirectionalLights);
    gl::setUniform(u.numSpotLights, numSpotLights);
}

template<typename T>
void Material::setCustomUniformsOfType(const Material::LocationToUniformValue<T>& values) {

    for (auto& [location, value] : values) {
        gl::setUniform(location, value);
    }
}

template<>
void Material::setCustomUniformsOfType<std::shared_ptr<Texture>>(const Material::LocationToUniformValue<std::shared_ptr<Texture>>& values) {

    GLenum i = 0;
    for (auto& [location, value] : values) {

        // Activate texture slot i
        glActiveTexture(GL_TEXTURE0 + i);
        // Bind the texture to the current active slot
        glBindTexture(GL_TEXTURE_2D, value->getId());
        // Tell the shader the texture slot for the diffuse texture is slot i
        glUniform1i(location, i);

        i += 1;
        if (i > GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS) {

            // TODO have materials (and maybe other resources) have a name to display in these error messages.
            std::cout << "Too many textures for this material." << std::endl;
            break;
        }
    }
}

void Material::setCustomUniforms() {

    std::apply([this](auto&&... args){(setCustomUniformsOfType(args), ...);}, m_uniformValues);
}

Material::BuiltinUniformLocations Material::cacheBuiltinUniformLocations() {

    BuiltinUniformLocations u;

    u.model      = m_shader->getUniformLocation("matrixModel");
    u.view       = m_shader->getUniformLocation("matrixView");
    u.projection = m_shader->getUniformLocation("matrixProjection");
    u.pvm        = m_shader->getUniformLocation("matrixPVM");

    u.time = m_shader->getUniformLocation("time");

    u.viewPosition = m_shader->getUniformLocation("viewPosition");

    // Point lights
    u.numPointLights = m_shader->getUniformLocation("numPointLights");
    for (int i = 0; i < MAX_NUM_POINT_LIGHTS; ++i) {

        std::string prefix = "pointLights[" + std::to_string(i) + "].";
        auto& locations = u.pointLights[i];

        locations.color = m_shader->getUniformLocation(prefix + "color");
        if (locations.color == -1)
            break;

        locations.colorAmbient = m_shader->getUniformLocation(prefix + "colorAmbient");
        locations.position     = m_shader->getUniformLocation(prefix + "position");
        locations.falloffConstant  = m_shader->getUniformLocation(prefix + "falloffConstant");
        locations.falloffLinear    = m_shader->getUniformLocation(prefix + "falloffLinear");
        locations.falloffQuadratic = m_shader->getUniformLocation(prefix + "falloffQuadratic");

        m_numSupportedPointLights = i + 1;
    }

    // Directional lights
    u.numDirectionalLights = m_shader->getUniformLocation("numDirectionalLights");
    for (int i = 0; i < MAX_NUM_DIRECTIONAL_LIGHTS; ++i) {

        std::string prefix = "directionalLights[" + std::to_string(i) + "].";
        auto& locations = u.directionalLights[i];

        locations.color = m_shader->getUniformLocation(prefix + "color");
        if (locations.color == -1)
            break;

        locations.colorAmbient = m_shader->getUniformLocation(prefix + "colorAmbient");
        locations.direction    = m_shader->getUniformLocation(prefix + "direction");
        locations.falloffConstant  = m_shader->getUniformLocation(prefix + "falloffConstant");
        locations.falloffLinear    = m_shader->getUniformLocation(prefix + "falloffLinear");
        locations.falloffQuadratic = m_shader->getUniformLocation(prefix + "falloffQuadratic");

        m_numSupportedDirectionalLights = i + 1;
    }

    // Spot lights
    u.numSpotLights = m_shader->getUniformLocation("numSpotLights");
    for (int i = 0; i < MAX_NUM_SPOT_LIGHTS; ++i) {

        std::string prefix = "spotLights[" + std::to_string(i) + "].";
        auto& locations = u.spotLights[i];

        locations.color = m_shader->getUniformLocation(prefix + "color");
        if (locations.color == -1)
            break;

        locations.colorAmbient = m_shader->getUniformLocation(prefix + "colorAmbient");
        locations.position     = m_shader->getUniformLocation(prefix + "position");
        locations.direction    = m_shader->getUniformLocation(prefix + "direction");
        locations.falloffConstant  = m_shader->getUniformLocation(prefix + "falloffConstant");
        locations.falloffLinear    = m_shader->getUniformLocation(prefix + "falloffLinear");
        locations.falloffQuadratic = m_shader->getUniformLocation(prefix + "falloffQuadratic");
        locations.innerCutoff      = m_shader->getUniformLocation(prefix + "innerCutoff");
        locations.outerCutoff      = m_shader->getUniformLocation(prefix + "outerCutoff");

        m_numSupportedSpotLights = i + 1;
    }

    return u;
}

Material::AttributeLocations Material::cacheAttributeLocations() {

    AttributeLocations a;
    a.vertex = m_shader->getAttribLocation("vertex");
    a.normal = m_shader->getAttribLocation("normal");
    a.uv     = m_shader->getAttribLocation("uv");

    return a;
}

void Material::detectAllUniforms() {

    std::vector<UniformInfo> uniforms = m_shader->getAllUniforms();

    //std::cout << "Uniforms: " << std::endl;
    for (auto& info : uniforms) {

        //std::cout << info.location << " : " << info.name << std::endl;
        m_uniforms[info.name] = info;
    }
    //std::cout << std::endl;
}

void Material::setUniformsPointLight(
    const Material::BuiltinUniformLocations::PointLightLocations& locations,
    const Light& light,
    const Transform& tf
) {
    if (valid(locations.position))
        gl::setUniform(locations.position, tf.getWorldPosition());

    gl::setUniform(locations.color       , light.color * light.intensity);
    gl::setUniform(locations.colorAmbient, light.colorAmbient * light.intensity);
    gl::setUniform(locations.falloffConstant , light.falloff.constant);
    gl::setUniform(locations.falloffLinear   , light.falloff.linear);
    gl::setUniform(locations.falloffQuadratic, light.falloff.quadratic);
}

void Material::setUniformDirectionalLight(
    const Material::BuiltinUniformLocations::DirectionalLightLocations& locations,
    const Light& light,
    const Transform& tf
) {
    if (valid(locations.direction))
        gl::setUniform(locations.direction, glm::normalize(glm::vec3(tf.getWorldTransform()[2])));

    gl::setUniform(locations.color       , light.color * light.intensity);
    gl::setUniform(locations.colorAmbient, light.colorAmbient * light.intensity);
    gl::setUniform(locations.falloffConstant , light.falloff.constant);
    gl::setUniform(locations.falloffLinear   , light.falloff.linear);
    gl::setUniform(locations.falloffQuadratic, light.falloff.quadratic);
}

void Material::setUniformSpotLight(
    const BuiltinUniformLocations::SpotLightLocations& locations,
    const Light& light,
    const Transform& tf
) {
    if (valid(locations.position))
        gl::setUniform(locations.position, tf.getWorldPosition());

    if (valid(locations.direction))
        gl::setUniform(locations.direction, glm::normalize(glm::vec3(tf.getWorldTransform()[2])));

    gl::setUniform(locations.color       , light.color * light.intensity);
    gl::setUniform(locations.colorAmbient, light.colorAmbient * light.intensity);
    gl::setUniform(locations.falloffConstant , light.falloff.constant);
    gl::setUniform(locations.falloffLinear   , light.falloff.linear);
    gl::setUniform(locations.falloffQuadratic, light.falloff.quadratic);
    gl::setUniform(locations.innerCutoff, light.spotlightInnerCutoff);
    gl::setUniform(locations.outerCutoff, glm::min(light.spotlightInnerCutoff, light.spotlightOuterCutoff));
}