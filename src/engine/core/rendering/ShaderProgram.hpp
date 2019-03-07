#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <GL/glew.h>
#include <vector>
#include <string>
#include <memory>
#include <vector>
#include "Resources.h"
#include "config.hpp"
#include "GLSetUniform.h"

namespace en {

	struct UniformInfo {

		GLint location = -1;
		std::string name;
	};

    /**
     * Generic shader program to which you can add separate shaders.
     * Nice exercise for the reader: make it possible to add shaders by passing in the code as a string instead of through a file.
     *
     * Usage:
     *  -create shader program
     *  -add shaders
     *  -finalize shader program
     *  -use shader program
     *
     * See the example material classes for a demo.
     */
	class ShaderProgram {

	public:

		ShaderProgram();
		virtual ~ShaderProgram();

		// Add a shader of a specific type (eg GL_VERTEX_SHADER / GL_FRAGMENT_SHADER)
		bool addShader(GLuint shaderType, const std::string& filepath);
		// Link and compile all added shaders
		void finalize();

		void use();

		// Get access to uniforms within the shader
		GLint getUniformLocation(const std::string& pName);

		// Get access to attributes within the shader
		GLint getAttribLocation(const std::string& pName);

		template<typename T>
		void setUniformValue(const std::string& name, T&& value);

		std::vector<UniformInfo> getAllUniforms();

	private:

		GLuint m_programId = 0;
		std::vector<GLuint> m_shaderIds;

		GLuint compileShader(GLuint pShaderType, const std::string& pShaderSource);
	};

	template<typename T>
	inline void ShaderProgram::setUniformValue(const std::string& name, T&& value) {

		GLint location = getUniformLocation(name);
		if (location == -1)
			throw "No such uniform!";

		gl::setUniform(location, std::forward<T>(value));
	}

	template<>
	struct ResourceLoader<ShaderProgram> {

        inline static std::shared_ptr<ShaderProgram> load(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {

            auto shader = std::make_shared<ShaderProgram>();
            shader->addShader(GL_VERTEX_SHADER, vertexShaderPath);
            shader->addShader(GL_FRAGMENT_SHADER, fragmentShaderPath);
            shader->finalize();
            return shader;
        }

		inline static std::shared_ptr<ShaderProgram> load(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& geometryShaderPath) {

			auto shader = std::make_shared<ShaderProgram>();
			shader->addShader(GL_VERTEX_SHADER  , vertexShaderPath);
			shader->addShader(GL_GEOMETRY_SHADER, geometryShaderPath);
			shader->addShader(GL_FRAGMENT_SHADER, fragmentShaderPath);
			shader->finalize();
			return shader;
		}

        inline static std::shared_ptr<ShaderProgram> load(const std::string& name) {

        	std::string prefix = config::SHADER_PATH + name;
            return load(
                prefix + ".vs",
                prefix + ".fs",
                prefix + ".gs"
			);
        }
    };
}

#endif // SHADERPROGRAM_HPP

