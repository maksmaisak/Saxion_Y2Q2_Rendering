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

WobblingMaterial::WobblingMaterial(Texture* pDiffuseTexture) : _diffuseTexture(pDiffuseTexture) {
    _lazyInitializeShader();
}

void WobblingMaterial::_lazyInitializeShader() {

    if (_shader) return;

    _shader = new ShaderProgram();
    _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "wobble.vs");
    _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "wobble.fs");
    _shader->finalize();
}

void WobblingMaterial::setDiffuseTexture(Texture* pDiffuseTexture) {
    _diffuseTexture = pDiffuseTexture;
}

void WobblingMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {

    _shader->use();

    glUniform1f(_shader->getUniformLocation("time"), GameTime::now().asSeconds());
    glUniform1f(_shader->getUniformLocation("timeScale"), 10);
    glUniform1f(_shader->getUniformLocation("phaseOffsetPerUnitDistance"), 6);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
    glUniform1i(_shader->getUniformLocation("diffuseTexture"), 0);

    glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
    glUniformMatrix4fv(_shader->getUniformLocation("mvpMatrix"), 1, GL_FALSE, glm::value_ptr(mvpMatrix));

    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(
        _shader->getAttribLocation("vertex"),
        _shader->getAttribLocation("normal"),
        _shader->getAttribLocation("uv")
    );
}