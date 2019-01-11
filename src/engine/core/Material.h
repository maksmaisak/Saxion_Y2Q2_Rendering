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
#include "TupleUtils.h"

namespace en {

    /// A generic material that works with a given shader.
    /// Automatically sets `built-in` uniforms like transformation matrices, time and lighting data.
    /// Use material.setUniformValue to set material-specific values for uniforms other than the built-in ones.
    /// The material will set those when it's time to render.
    class Material : public AbstractMaterial {

    public:

        explicit Material(const std::string& shaderFilename);
        explicit Material(std::shared_ptr<ShaderProgram> shader);

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

        static constexpr int MAX_NUM_POINT_LIGHTS = 10;

        std::shared_ptr<ShaderProgram> m_shader;

        int m_numSupportedPointLights = 0;

        struct BuiltinUniformLocations {

            GLint model       = -1;
            GLint view        = -1;
            GLint projection  = -1;
            GLint pvm         = -1;

            GLint time = -1;

            GLint viewPosition = -1;

            struct LightPointLocations {

                GLint position = -1;
                GLint color = -1;

            } pointLights[MAX_NUM_POINT_LIGHTS];
            int numPointLights = -1;

        } m_builtinUniformLocations;

        struct AttributeLocations {

            GLint vertex = -1;
            GLint normal = -1;
            GLint uv     = -1;

        } m_attributeLocations;

        std::unordered_map<std::string, UniformInfo> m_uniforms;

        // Only types listed here will be supported as custom uniform values,
        // i.e settable via material.setUniform
        UniformValues<
            GLint, GLuint, GLfloat,
            glm::vec2, glm::vec3, glm::vec4,
            glm::mat4,
            std::shared_ptr<Texture>
        > m_uniformValues;

        void detectAllUniforms();
        BuiltinUniformLocations cacheBuiltinUniformLocations();
        AttributeLocations cacheAttributeLocations();

        void setBuiltinUniforms(Engine* engine, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& perspectiveMatrix);
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

        static_assert(
            has_type_v<NameToLocationValuePair<T>, decltype(m_uniformValues)>,
            "This type is unsupported for custom uniforms."
        );

        auto& values = std::get<NameToLocationValuePair<T>>(m_uniformValues);
        values[name] = {it->second.location, value};
    }
}

#endif //SAXION_Y2Q2_RENDERING_MATERIAL_H
