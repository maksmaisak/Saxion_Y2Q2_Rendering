#ifndef COLORMATERIAL_HPP
#define COLORMATERIAL_HPP

#include "GL/glew.h"
#include "materials/AbstractMaterial.hpp"
#include "ShaderProgram.hpp"

/**
 * This is about the simplest material we can come up with, it demonstrates how to
 * render a single color material without caching, passing in all the matrices we require separately.
 */
class ColorMaterial : public AbstractMaterial
{
    public:

        explicit ColorMaterial(glm::vec3 pColor = glm::vec3(1,0,0));
        virtual ~ColorMaterial() = default;

        virtual void render(
            en::Engine* pEngine, Mesh* pMesh,
            const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix
        ) override;

        //in rgb values
        void setDiffuseColor(glm::vec3 pDiffuseColor);

    private:
        inline static std::shared_ptr<en::ShaderProgram> m_shader = nullptr;

        //this one is unique per instance of color material
        glm::vec3 diffuseColor;
};

#endif // COLORMATERIAL_HPP