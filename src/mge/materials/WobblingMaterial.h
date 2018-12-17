//
// Created by Maksym Maisak on 17/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_WOBBLINGMATERIAL_H
#define SAXION_Y2Q2_RENDERING_WOBBLINGMATERIAL_H

#include "GL/glew.h"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/Texture.hpp"

class ShaderProgram;

class WobblingMaterial : public AbstractMaterial
{
public:
    explicit WobblingMaterial(Texture* pDiffuseTexture);
    virtual ~WobblingMaterial() = default;

    void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;
    void setDiffuseTexture (Texture* pDiffuseTexture);

private:
    inline static ShaderProgram* _shader = nullptr;
    static void _lazyInitializeShader();

    Texture* _diffuseTexture;
};


#endif //SAXION_Y2Q2_RENDERING_WOBBLINGMATERIAL_H
