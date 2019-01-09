//
// Created by Maksym Maisak on 2019-01-09.
//

#ifndef SAXION_Y2Q2_RENDERING_MATERIAL_H
#define SAXION_Y2Q2_RENDERING_MATERIAL_H

#include <memory>
#include <string>
#include <unordered_map>
#include "AbstractMaterial.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

namespace en {

    /// A generic material that works with a given shader.
    /// Automatically sets predetermined uniforms like transformation matricies and lights on render.
    class Material : public AbstractMaterial {

    public:

        Material(const std::string& shaderFilename);
        Material(std::shared_ptr<ShaderProgram> shader);

        void render(Engine* engine, Mesh* mesh,
            const glm::mat4& modelMatrix,
            const glm::mat4& viewMatrix,
            const glm::mat4& perspectiveMatrix
        ) override;

        void setUniformVec3(const std::string& name, const glm::vec3& value);
        void setUniformVec4(const std::string& name, const glm::vec4& value);
        void setUniformMat4(const std::string& name, const glm::mat4& value);

    private:

        void setSupportedUniforms(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& perspectiveMatrix);
        void setCustomUniforms();

        std::shared_ptr<ShaderProgram> m_shader;

        struct UniformLocations {

            GLint model       = -1;
            GLint view        = -1;
            GLint perspective = -1;
            GLint pvm         = -1;

            GLint time = -1;

        } m_uniformLocations;

        struct AttributeLocations {

            GLint vertex = -1;
            GLint normal = -1;
            GLint uv     = -1;

        } m_attributeLocations;

        std::unordered_map<std::string, UniformInfo> m_uniforms;

        // The necessary info for assigning a material-specific value for a uniform.
        template<typename T>
        struct LocationValuePair {
            GLint location = -1;
            T value;
        };

        // TODO Make this a mapping from location instead of from name.
        template<typename T>
        using NameToLocationValuePair = std::unordered_map<std::string, LocationValuePair<T>>;

        // TODO Have a tuple for all these. Use std::get<T> to get NameToLocationValuePair<T>
        NameToLocationValuePair<glm::mat4> m_nameToUniformMat4;
        NameToLocationValuePair<glm::vec3> m_nameToUniformVec3;
        NameToLocationValuePair<glm::vec4> m_nameToUniformVec4;
        NameToLocationValuePair<std::shared_ptr<Texture>> m_nameToUniformTexture;

        void detectAllUniforms();
        UniformLocations   getUniformLocations();
        AttributeLocations getAttributeLocations();
    };
}

#endif //SAXION_Y2Q2_RENDERING_MATERIAL_H
