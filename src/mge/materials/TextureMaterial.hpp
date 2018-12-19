#ifndef TEXTUREMATERIAL_HPP
#define TEXTUREMATERIAL_HPP

#include "mge/materials/AbstractMaterial.hpp"
#include "GL/glew.h"
#include <memory>

class ShaderProgram;
class Texture;

/**
 * This material is already a little bit more complicated, instead of a color we can pass in a texture,
 * all attributes and uniforms are cached and we precompute the MVP matrix passing it in as one entity.
 */
class TextureMaterial : public AbstractMaterial
{
    public:
        explicit TextureMaterial(const std::string& filename);
        explicit TextureMaterial(std::shared_ptr<Texture> pDiffuseTexture);
        virtual ~TextureMaterial() = default;

        virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

        void setDiffuseTexture(std::shared_ptr<Texture> pDiffuseTexture);

    private:
        inline static ShaderProgram* _shader = nullptr;
        static void _lazyInitializeShader();

        //in this example we cache all identifiers for uniforms & attributes
        inline static GLint _uMVPMatrix = 0;
        inline static GLint _uDiffuseTexture = 0;
        inline static GLint _aVertex = 0;
        inline static GLint _aNormal = 0;
        inline static GLint _aUV = 0;

        std::shared_ptr<Texture> _diffuseTexture;
};

#endif // TEXTUREMATERIAL_HPP
