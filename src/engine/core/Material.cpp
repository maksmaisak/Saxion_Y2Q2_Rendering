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

    // Add point lights
    int numPointLights = 0;
    for (Entity e : registry.with<en::Transform, en::Light>()) {

        // TODO sort lights by proximity, pick the closest ones.

        if (numPointLights >= m_numSupportedPointLights)
            break;

        auto& light = registry.get<en::Light>(e);
        auto& tf = registry.get<en::Transform>(e);

        if (light.kind != en::Light::Kind::POINT) // TODO Add support for directional lights
            continue;

        auto& locations = u.pointLights[numPointLights];

        if (valid(locations.position))
            gl::setUniform(locations.position, tf.getWorldPosition());

        gl::setUniform(locations.color       , light.color);
        gl::setUniform(locations.colorAmbient, light.colorAmbient);
        gl::setUniform(locations.falloffConstant , light.falloff.constant);
        gl::setUniform(locations.falloffLinear   , light.falloff.linear);
        gl::setUniform(locations.falloffQuadratic, light.falloff.quadratic);

        numPointLights += 1;
    }
    gl::setUniform(u.numPointLights, numPointLights);
}

template<typename T>
void Material::setCustomUniformsOfType(const Material::NameToLocationValuePair<T>& values) {

    for (auto& [name, locationValuePair] : values) {
        gl::setUniform(locationValuePair.location, locationValuePair.value);
    }
}

template<>
void Material::setCustomUniformsOfType<std::shared_ptr<Texture>>(const Material::NameToLocationValuePair<std::shared_ptr<Texture>>& values) {

    GLenum i = 0;
    for (auto& [name, locationValuePair] : values) {

        // Activate texture slot i
        glActiveTexture(GL_TEXTURE0 + i);
        // Bind the texture to the current active slot
        glBindTexture(GL_TEXTURE_2D, locationValuePair.value->getId());
        // Tell the shader the texture slot for the diffuse texture is slot i
        glUniform1i(locationValuePair.location, i);

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

    u.numPointLights = m_shader->getUniformLocation("numPointLights");
    for (int i = 0; i < MAX_NUM_POINT_LIGHTS; ++i) {

        std::string prefix = "pointLights[" + std::to_string(i) + "].";
        auto& locations = u.pointLights[i];

        locations.color        = m_shader->getUniformLocation(prefix + "color");
        locations.colorAmbient = m_shader->getUniformLocation(prefix + "colorAmbient");
        locations.position     = m_shader->getUniformLocation(prefix + "position");
        locations.falloffConstant  = m_shader->getUniformLocation(prefix + "falloffConstant");
        locations.falloffLinear    = m_shader->getUniformLocation(prefix + "falloffLinear");
        locations.falloffQuadratic = m_shader->getUniformLocation(prefix + "falloffQuadratic");

        if (locations.color == -1)
            break;

        m_numSupportedPointLights = i + 1;
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

    std::cout << "Uniforms: " << std::endl;
    for (auto& info : uniforms) {

        std::cout << info.location << " : " << info.name << std::endl;
        m_uniforms[info.name] = info;
    }
    std::cout << std::endl;
}
