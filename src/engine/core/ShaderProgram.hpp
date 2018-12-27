#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <GL/glew.h>
#include <vector>
#include <string>
#include <memory>
#include "Resources.h"
#include "mge/config.hpp"

namespace en {

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

		//add a shader of a specific type (eg GL_VERTEX_SHADER / GL_FRAGMENT_SHADER)
		void addShader(GLuint pShaderType, const std::string& pShaderPath);

		//link and compile all added shaders
		void finalize();

		//tell opengl this is now the current shader program
		void use();

		//get access to uniforms within the shader
		GLuint getUniformLocation(const std::string& pName);

		//get access to attributes within the shader
		GLuint getAttribLocation(const std::string& pName);

	private:

		GLint m_programId = 0;
		std::vector<GLuint> m_shaderIds;

		std::string readFile(const std::string& pShaderPath);

		GLuint compileShader(GLuint pShaderType, const std::string& pShaderSource);
	};

	template<>
	struct ResourceLoader<ShaderProgram> {

        inline static std::shared_ptr<ShaderProgram> load(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {

            auto shader = std::make_shared<ShaderProgram>();
            shader->addShader(GL_VERTEX_SHADER, vertexShaderPath);
            shader->addShader(GL_FRAGMENT_SHADER, fragmentShaderPath);
            shader->finalize();
            return shader;
        }

        inline static std::shared_ptr<ShaderProgram> load(const std::string& name) {

            return load(
                config::MGE_SHADER_PATH + name + ".vs",
                config::MGE_SHADER_PATH + name + ".fs"
            );
        }
    };
}

#endif // SHADERPROGRAM_HPP

