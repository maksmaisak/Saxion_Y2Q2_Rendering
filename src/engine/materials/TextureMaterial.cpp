#include <utility>

#include "glm.hpp"

#include "TextureMaterial.hpp"
#include "engine/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "engine/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "engine/core/ShaderProgram.hpp"
#include "mge/config.hpp"

#include "Resources.h"

TextureMaterial::TextureMaterial(std::shared_ptr<Texture> pDiffuseTexture) : _diffuseTexture(std::move(pDiffuseTexture)) {
    _lazyInitializeShader();
}

TextureMaterial::TextureMaterial(const std::string& filename) : TextureMaterial(en::Resources<Texture>::get(filename)) {}

void TextureMaterial::_lazyInitializeShader() {

    if (_shader) return;

    _shader = new en::ShaderProgram();
    _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "texture.vs");
    _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "texture.fs");
    _shader->finalize();

    //cache all the uniform and attribute indexes
    _uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
    _uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");

    _aVertex = _shader->getAttribLocation("vertex");
    _aNormal = _shader->getAttribLocation("normal");
    _aUV =     _shader->getAttribLocation("uv");
}

void TextureMaterial::setDiffuseTexture(std::shared_ptr<Texture> pDiffuseTexture) {
    _diffuseTexture = pDiffuseTexture;
}

void TextureMaterial::render(en::Engine* pEngine, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix,
                             const glm::mat4& pProjectionMatrix) {
    if (!_diffuseTexture) return;

    _shader->use();

    //Print the number of lights in the scene and the position of the first light.
    //It is not used, but this demo is just meant to show you THAT materials can access the lights in a world
    //if (pWorld->getLightCount() > 0) {
    //    std::cout << "TextureMaterial has discovered light is at position:" << pWorld->getLightAt(0)->getLocalPosition() << std::endl;
    //}

    //setup texture slot 0
    glActiveTexture(GL_TEXTURE0);
    //bind the texture to the current active slot
    glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
    //tell the shader the texture slot for the diffuse texture is slot 0
    glUniform1i (_uDiffuseTexture, 0);

    //pass in a precalculate mvp matrix (see texture material for the opposite)
    glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
    glUniformMatrix4fv ( _uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}