//
// Created by Maksym Maisak on 2019-01-09.
//

#ifndef SAXION_Y2Q2_RENDERING_MATERIAL_H
#define SAXION_Y2Q2_RENDERING_MATERIAL_H

#include <memory>
#include <string>
#include <unordered_map>
#include <tuple>
#include "AbstractMaterial.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

namespace en {

    /// A generic material that works with a given shader.
    /// Automatically sets `built-in` uniforms like transformation matricies, time and lighing data.
    /// Use material.setUniformValue to set material-specific values for uniforms other than the built-in ones.
    /// The material will set those when it's time to render.
    class Material : public AbstractMaterial {

    public:

        Material(const std::string& shaderFilename);
        Material(std::shared_ptr<ShaderProgram> shader);

        void render(Engine* engine, Mesh* mesh,
            const glm::mat4& modelMatrix,
            const glm::mat4& viewMatrix,
            const glm::mat4& perspectiveMatrix
        ) override;

        template<typename T>
        void setUniformValue(const std::string& name, const T& value);

    private:

        // The necessary info for assigning a material-specific value for a uniform.
        template<typename T>
        struct UniformLocationValuePair {
            GLint location = -1;
            T value;
        };

        // TODO Make this a mapping from location instead of from name.
        template<typename T>
        using NameToLocationValuePair = std::unordered_map<std::string, UniformLocationValuePair<T>>;

        template<typename... T>
        using UniformValues = std::tuple<NameToLocationValuePair<T>...>;

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

        // Only types listed here will be supported as custom uniform values,
        // i.e settable via material.setUniform
        UniformValues<
            glm::vec2, glm::vec3, glm::vec4,
            glm::mat4,
            std::shared_ptr<Texture>
        > m_uniformValues;

        void detectAllUniforms();
        UniformLocations   cacheUniformLocations();
        AttributeLocations cacheAttributeLocations();

        void setSupportedUniforms(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& perspectiveMatrix);
        void setCustomUniforms();

        template<typename T>
        void setCustomUniformsOfType(const NameToLocationValuePair<T>& values);
    };

    template<typename T>
    inline void Material::setUniformValue(const std::string& name, const T& value) {

        auto it = m_uniforms.find(name);
        if (it == m_uniforms.end()) {
            throw "No such uniform: " + name;
        }

        auto& values = std::get<NameToLocationValuePair<T>>(m_uniformValues);
        values[name] = {it->second.location, value};
    }
}

#endif //SAXION_Y2Q2_RENDERING_MATERIAL_H
