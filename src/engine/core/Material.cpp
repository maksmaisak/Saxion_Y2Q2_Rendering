#include <utility>

//
// Created by Maksym Maisak on 2019-01-09.
//

#include <cassert>
#include <iostream>
#include <any>
#include "Material.h"
#include "Resources.h"
#include "Mesh.hpp"
#include "GLSetUniform.h"
#include "TupleUtils.h"

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

    setSupportedUniforms(modelMatrix, viewMatrix, perspectiveMatrix);
    setCustomUniforms();

    const auto& a = m_attributeLocations;
    mesh->streamToOpenGL(a.vertex, a.normal, a.uv);
}

inline bool valid(GLint location) {return location != -1;}

void Material::setSupportedUniforms(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& perspectiveMatrix) {

    const auto& u = m_builtinUniformLocations;

    if (valid(u.model      )) gl::setUniform(u.model      , modelMatrix      );
    if (valid(u.view       )) gl::setUniform(u.view       , viewMatrix       );
    if (valid(u.perspective)) gl::setUniform(u.perspective, perspectiveMatrix);
    if (valid(u.pvm        )) gl::setUniform(u.pvm, perspectiveMatrix * viewMatrix * modelMatrix);
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
    u.model       = m_shader->getUniformLocation("matrixModel");
    u.view        = m_shader->getUniformLocation("matrixView");
    u.perspective = m_shader->getUniformLocation("matrixPerspective");
    u.pvm         = m_shader->getUniformLocation("matrixPVM");

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
}
