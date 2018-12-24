#include "glm.hpp"

#include "ColorMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/GameObject.hpp"
#include "engine/core/Mesh.hpp"
#include "engine/core/ShaderProgram.hpp"
#include "Resources.h"

ColorMaterial::ColorMaterial(glm::vec3 pDiffuseColor) : diffuseColor(pDiffuseColor) {

    if (m_shader) return;

    m_shader = en::Resources<en::ShaderProgram>::get("color",
        config::MGE_SHADER_PATH + "color.vs",
        config::MGE_SHADER_PATH + "color.fs"
    );
}

void ColorMaterial::setDiffuseColor(glm::vec3 pDiffuseColor) {

    diffuseColor = pDiffuseColor;
}

void ColorMaterial::render(en::Engine* pEngine, Mesh* pMesh,
    const glm::mat4& pModelMatrix,
    const glm::mat4& pViewMatrix,
    const glm::mat4& pProjectionMatrix
) {

    m_shader->use();

    //set the material color
    glUniform3fv(m_shader->getUniformLocation("diffuseColor"), 1, glm::value_ptr(diffuseColor));

    //pass in all MVP matrices separately
    glUniformMatrix4fv(m_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
    glUniformMatrix4fv(m_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
    glUniformMatrix4fv(m_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));

    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(
        m_shader->getAttribLocation("vertex"),
        m_shader->getAttribLocation("normal"),
        m_shader->getAttribLocation("uv")
    );

}
