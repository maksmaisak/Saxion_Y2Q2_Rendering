#ifndef ABSTRACTMATERIAL_HPP
#define ABSTRACTMATERIAL_HPP

#include "glm.hpp"
#include "Engine.h"
#include "ShaderProgram.hpp"
#include "DepthMaps.h"

namespace en {
    class Mesh;
}

/**
 * Base calss for a material. Wraps around a shader. For most use cases just use en::Material.
 */
class AbstractMaterial {

    public:
        AbstractMaterial() = default;
        virtual ~AbstractMaterial() = default;
        AbstractMaterial(const AbstractMaterial&) = delete;
        AbstractMaterial& operator=(const AbstractMaterial&) = delete;
        AbstractMaterial(AbstractMaterial&&) = default;
        AbstractMaterial& operator=(AbstractMaterial&&) = default;

        /**
         * Render the given mesh in the given engine using the given mvp matrices. Implement in subclass.
         */
        virtual void render(
            const en::Mesh* mesh,
            en::Engine* pEngine,
            en::DepthMaps* depthMaps,
            const glm::mat4& matrixModel,
            const glm::mat4& matrixView,
            const glm::mat4& matrixProjection
        ) = 0;
};

#endif // ABSTRACTMATERIAL_HPP
