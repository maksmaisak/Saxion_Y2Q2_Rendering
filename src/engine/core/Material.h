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
#include "Light.h"
#include "Transform.h"

namespace en {

    class LuaState;

    /// A generic material that works with a given shader.
    /// Automatically sets `built-in` uniforms like transformation matrices, time and lighting data.
    /// Use material.setUniformValue to set material-specific values for uniforms other than the built-in ones.
    /// The material will set those when it's time to render.
    class Material : public AbstractMaterial {

    public:

        explicit Material(const std::string& shaderFilename);
        explicit Material(std::shared_ptr<ShaderProgram> shader);
        /// Makes a material from the table on top of stack in the given lua state
        explicit Material(LuaState& lua);

        void render(Engine* engine, Mesh* mesh,
            const glm::mat4& modelMatrix,
            const glm::mat4& viewMatrix,
            const glm::mat4& perspectiveMatrix
        ) override;

        template<typename T>
        void setUniformValue(const std::string& name, const T& value);

    private:

        // TODO Make this a mapping from location instead of from name.
        template<typename T>
        using LocationToUniformValue = std::unordered_map<GLint, T>;

        template<typename... T>
        using UniformValues = std::tuple<LocationToUniformValue<T>...>;

        static constexpr int MAX_NUM_POINT_LIGHTS = 10;
        static constexpr int MAX_NUM_DIRECTIONAL_LIGHTS = 10;
        static constexpr int MAX_NUM_SPOT_LIGHTS = 10;

        std::shared_ptr<ShaderProgram> m_shader;

        int m_numSupportedPointLights = 0;
        int m_numSupportedDirectionalLights = 0;
        int m_numSupportedSpotLights = 0;

        struct BuiltinUniformLocations {

            GLint model       = -1;
            GLint view        = -1;
            GLint projection  = -1;
            GLint pvm         = -1;

            GLint time = -1;

            GLint viewPosition = -1;

            GLint numPointLights = -1;
            struct PointLightLocations {

                GLint position = -1;

                GLint color        = -1;
                GLint colorAmbient = -1;

                GLint falloffConstant  = -1;
                GLint falloffLinear    = -1;
                GLint falloffQuadratic = -1;

            } pointLights[MAX_NUM_POINT_LIGHTS];

            GLint numDirectionalLights = -1;
            struct DirectionalLightLocations {

                GLint direction = -1;

                GLint color        = -1;
                GLint colorAmbient = -1;

                GLint falloffConstant  = -1;
                GLint falloffLinear    = -1;
                GLint falloffQuadratic = -1;

            } directionalLights[MAX_NUM_DIRECTIONAL_LIGHTS];

            GLint numSpotLights = -1;
            struct SpotLightLocations {

                GLint position  = -1;
                GLint direction = -1;

                GLint color        = -1;
                GLint colorAmbient = -1;

                GLint falloffConstant  = -1;
                GLint falloffLinear    = -1;
                GLint falloffQuadratic = -1;
                GLint innerCutoff = -1;
                GLint outerCutoff = -1;

            } spotLights[MAX_NUM_SPOT_LIGHTS];;

        } m_builtinUniformLocations;

        struct AttributeLocations {

            GLint vertex = -1;
            GLint normal = -1;
            GLint uv     = -1;

        } m_attributeLocations;

        // All uniforms in the shader.
        std::unordered_map<std::string, UniformInfo> m_uniforms;

        // Values of custom material-specific uniforms.
        // A tuple of maps between locations and values.
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
        void setCustomUniformsOfType(const LocationToUniformValue<T>& values);

        void setUniformsPointLight(const BuiltinUniformLocations::PointLightLocations& locations, const Light& light, const Transform& tf);
        void setUniformDirectionalLight(const BuiltinUniformLocations::DirectionalLightLocations& locations, const Light& light, const Transform& tf);
        void setUniformSpotLight(const BuiltinUniformLocations::SpotLightLocations& locations, const Light& light, const Transform& tf);
    };

    template<typename T>
    inline void Material::setUniformValue(const std::string& name, const T& value) {

        auto it = m_uniforms.find(name);
        if (it == m_uniforms.end()) {
            throw "No such uniform: " + name;
        }

        static_assert(
            has_type_v<LocationToUniformValue<T>, decltype(m_uniformValues)>,
            "This type is unsupported for custom uniforms."
        );

        auto& values = std::get<LocationToUniformValue<T>>(m_uniformValues);
        values[it->second.location] = value;
    }
}

#endif //SAXION_Y2Q2_RENDERING_MATERIAL_H
