//
// Created by Maksym Maisak on 17/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_WOBBLINGMATERIAL_H
#define SAXION_Y2Q2_RENDERING_WOBBLINGMATERIAL_H

#include <memory>
#include "GL/glew.h"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/Texture.hpp"

class ShaderProgram;

class WobblingMaterial : public AbstractMaterial
{
public:
    explicit WobblingMaterial(std::shared_ptr<Texture> _diffuseTexture);
    explicit WobblingMaterial(const std::string& filename);
    virtual ~WobblingMaterial() = default;

    void render(en::Engine* pEngine, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix,
                const glm::mat4& pProjectionMatrix) override;
    void setDiffuseTexture(std::shared_ptr<Texture> pDiffuseTexture);

private:
    inline static ShaderProgram* _shader = nullptr;
    static void _lazyInitializeShader();

    std::shared_ptr<Texture> _diffuseTexture;
};


#endif //SAXION_Y2Q2_RENDERING_WOBBLINGMATERIAL_H
