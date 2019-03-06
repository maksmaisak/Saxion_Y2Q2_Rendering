//
// Created by Maksym Maisak on 17/12/18.
//

#include <GameTime.h>
#include "glm.hpp"

#include "WobblingMaterial.h"
#include "config.hpp"
#include "Mesh.hpp"
#include "ShaderProgram.hpp"

#include "Resources.h"

WobblingMaterial::WobblingMaterial(std::shared_ptr<Texture> pDiffuseTexture) : m_diffuseTexture(std::move(pDiffuseTexture)) {

    if (!m_shader)
        m_shader = en::Resources<en::ShaderProgram>::get("wobble");
}

WobblingMaterial::WobblingMaterial(const std::string& filename) : WobblingMaterial(en::Resources<Texture>::get(filename)) {}

void WobblingMaterial::setDiffuseTexture(std::shared_ptr<Texture> pDiffuseTexture) {
    m_diffuseTexture = pDiffuseTexture;
}

void WobblingMaterial::render(const en::Mesh* mesh, en::Engine* engine, en::DepthMaps* depthMaps, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {

    m_shader->use();

    glUniform1f(m_shader->getUniformLocation("time"), GameTime::now().asSeconds());
    glUniform1f(m_shader->getUniformLocation("timeScale"), 10);
    glUniform1f(m_shader->getUniformLocation("phaseOffsetPerUnitDistance"), 6);
    glUniform1f(m_shader->getUniformLocation("wobbleMultiplierMin"), 0.8f);
    glUniform1f(m_shader->getUniformLocation("wobbleMultiplierMax"), 1.2);
    glUniform1f(m_shader->getUniformLocation("transitionWobbleFactorMin"), 0.f);
    glUniform1f(m_shader->getUniformLocation("transitionWobbleFactorMax"), 1.f);
    glUniform4f(m_shader->getUniformLocation("transitionColor"), 0.01f, 0.5f, 1.f, 1.f);

    glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
    glUniformMatrix4fv(m_shader->getUniformLocation("mvpMatrix"), 1, GL_FALSE, glm::value_ptr(mvpMatrix));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_diffuseTexture->getId());
    glUniform1i(m_shader->getUniformLocation("diffuseTexture"), 0);

    //now inform mesh of where to stream its data
    mesh->render(
        m_shader->getAttribLocation("vertex"),
        m_shader->getAttribLocation("normal"),
        m_shader->getAttribLocation("uv")
    );
}