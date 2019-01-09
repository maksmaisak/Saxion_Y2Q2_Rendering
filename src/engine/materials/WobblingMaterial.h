//
// Created by Maksym Maisak on 17/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_WOBBLINGMATERIAL_H
#define SAXION_Y2Q2_RENDERING_WOBBLINGMATERIAL_H

#include <memory>
#include "GL/glew.h"
#include "AbstractMaterial.hpp"
#include "engine/core/Texture.hpp"

class WobblingMaterial : public AbstractMaterial
{
public:
    explicit WobblingMaterial(std::shared_ptr<Texture> _diffuseTexture);
    explicit WobblingMaterial(const std::string& filename);
    virtual ~WobblingMaterial() = default;

    void render(en::Engine* pEngine, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;
    void setDiffuseTexture(std::shared_ptr<Texture> pDiffuseTexture);

private:
    inline static std::shared_ptr<en::ShaderProgram> m_shader = nullptr;

    std::shared_ptr<Texture> m_diffuseTexture;
};


#endif //SAXION_Y2Q2_RENDERING_WOBBLINGMATERIAL_H
