//
// Created by Maksym Maisak on 17/12/18.
//

#include <GameTime.h>
#include "glm.hpp"

#include "WobblingMaterial.h"
#include "mge/config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/ShaderProgram.hpp"

#include "Resources.h"

WobblingMaterial::WobblingMaterial(std::shared_ptr<Texture> pDiffuseTexture) : _diffuseTexture(std::move(pDiffuseTexture)) {
    _lazyInitializeShader();
}

WobblingMaterial::WobblingMaterial(const std::string& filename) : WobblingMaterial(en::Resources<Texture>::get(filename)) {}

void WobblingMaterial::_lazyInitializeShader() {

    if (_shader) return;

    _shader = new ShaderProgram();
    _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "wobble.vs");
    _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "wobble.fs");
    _shader->finalize();
}

void WobblingMaterial::setDiffuseTexture(std::shared_ptr<Texture> pDiffuseTexture) {
    _diffuseTexture = pDiffuseTexture;
}

void WobblingMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {

    _shader->use();

    glUniform1f(_shader->getUniformLocation("time"), GameTime::now().asSeconds());
    glUniform1f(_shader->getUniformLocation("timeScale"), 10);
    glUniform1f(_shader->getUniformLocation("phaseOffsetPerUnitDistance"), 6);
    glUniform1f(_shader->getUniformLocation("wobbleMultiplierMin"), 0.8f);
    glUniform1f(_shader->getUniformLocation("wobbleMultiplierMax"), 1.2);
    glUniform1f(_shader->getUniformLocation("transitionWobbleFactorMin"), 0.f);
    glUniform1f(_shader->getUniformLocation("transitionWobbleFactorMax"), 1.f);
    glUniform4f(_shader->getUniformLocation("transitionColor"), 0.01f, 0.5f, 1.f, 1.f);

    glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
    glUniformMatrix4fv(_shader->getUniformLocation("mvpMatrix"), 1, GL_FALSE, glm::value_ptr(mvpMatrix));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
    glUniform1i(_shader->getUniformLocation("diffuseTexture"), 0);

    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(
        _shader->getAttribLocation("vertex"),
        _shader->getAttribLocation("normal"),
        _shader->getAttribLocation("uv")
    );
}