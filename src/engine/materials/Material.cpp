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

using namespace en;

inline bool valid(GLint location) {return location != -1;}

Material::Material(const std::string& shaderFilename) :
    Material(Resources<ShaderProgram>::get(shaderFilename)) {}

Material::Material(std::shared_ptr<ShaderProgram> shader) : m_shader(std::move(shader)) {

    assert(m_shader);

    m_uniformLocations   = getUniformLocations();
    m_attributeLocations = getAttributeLocations();
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

void Material::setSupportedUniforms(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& perspectiveMatrix) {

    static auto setUniformMatrix = [](GLint location, const glm::mat4& matrix) {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    };

    const auto& u = m_uniformLocations;

    if (valid(u.model      )) setUniformMatrix(u.model, modelMatrix);
    if (valid(u.view       )) setUniformMatrix(u.view , viewMatrix );
    if (valid(u.perspective)) setUniformMatrix(u.perspective, perspectiveMatrix);
    if (valid(u.pvm        )) setUniformMatrix(u.pvm, perspectiveMatrix * viewMatrix * modelMatrix);
}

void Material::setCustomUniforms() {

    for (auto& [name, pair] : m_nameToUniformMat4) {
        glUniformMatrix4fv(pair.location, 1, GL_FALSE, glm::value_ptr(pair.value));
    }

    for (auto& [name, pair] : m_nameToUniformVec3) {
        glUniform3fv(pair.location, 1, glm::value_ptr(pair.value));
    }

    for (auto& [name, pair] : m_nameToUniformVec4) {
        glUniform3fv(pair.location, 1, glm::value_ptr(pair.value));
    }

    GLenum i = 0;
    for (auto& [name, pair] : m_nameToUniformTexture) {

        // Activate texture slot i
        glActiveTexture(GL_TEXTURE0 + i);
        // Bind the texture to the current active slot
        glBindTexture(GL_TEXTURE_2D, pair.value->getId());
        // Tell the shader the texture slot for the diffuse texture is slot i
        glUniform1i(pair.location, i);

        i += 1;
        if (i > GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS) {

            // TODO have materials (and maybe other resources) have a name to display in these error messages.
            std::cout << "Too many textures for this material." << std::endl;
            break;
        }
    }
}

void Material::setUniformVec4(const std::string& name, const glm::vec4& value) {
    m_nameToUniformVec4[name] = {m_uniforms[name].location, value};
}

void Material::setUniformVec3(const std::string& name, const glm::vec3& value) {
    m_nameToUniformVec3[name] = {m_uniforms[name].location, value};
}

void Material::setUniformMat4(const std::string& name, const glm::mat4& value) {
    m_nameToUniformMat4[name] = {m_uniforms[name].location, value};
}

Material::UniformLocations Material::getUniformLocations() {

    UniformLocations u;
    u.model       = m_shader->getUniformLocation("matrixModel");
    u.view        = m_shader->getUniformLocation("matrixView");
    u.perspective = m_shader->getUniformLocation("matrixPerspective");
    u.pvm         = m_shader->getUniformLocation("matrixPVM");

    return u;
}

Material::AttributeLocations Material::getAttributeLocations() {

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