#include <iostream>
#include <fstream>
#include "engine/core/ShaderProgram.hpp"

namespace en {

    ShaderProgram::ShaderProgram() {

        m_programId = glCreateProgram();
        std::cout << std::endl << "Program created with id:" << m_programId << std::endl;
    }

    ShaderProgram::~ShaderProgram() {

        glDeleteProgram(m_programId);
    }

    void ShaderProgram::addShader(GLuint pShaderType, const std::string& pShaderPath) {

        std::string shaderCode = readFile(pShaderPath);
        GLuint shaderId = compileShader(pShaderType, shaderCode);

        if (shaderId != 0) {
            m_shaderIds.push_back(shaderId);
        }
    }

    void ShaderProgram::finalize() {

        for (unsigned int shaderId : m_shaderIds) {
            glAttachShader(m_programId, shaderId);
        }

        glLinkProgram(m_programId);

        // Check the program
        GLint didLinkSuccessfully = GL_FALSE;
        glGetProgramiv(m_programId, GL_LINK_STATUS, &didLinkSuccessfully);

        if (didLinkSuccessfully) {

            std::cout << "Program linked ok." << std::endl << std::endl;

        } else { // error, show message

            std::cerr << "Program linkage error:" << std::endl;
            int infoLogLength;
            glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &infoLogLength);
            char* errorMessage = new char[infoLogLength + 1];
            glGetProgramInfoLog(m_programId, infoLogLength, nullptr, errorMessage);
            std::cerr << errorMessage << std::endl << std::endl;
            delete[] errorMessage;
        }

        for (unsigned int shaderId : m_shaderIds) {
            glDeleteShader(shaderId);
        }
    }

    void ShaderProgram::use() {

        glUseProgram(m_programId);
    }

    GLuint ShaderProgram::getUniformLocation(const std::string& pName) {

        return glGetUniformLocation(m_programId, pName.c_str());
    }

    GLuint ShaderProgram::getAttribLocation(const std::string& pName) {

        return glGetAttribLocation(m_programId, pName.c_str());
    }

    std::string ShaderProgram::readFile(const std::string& pShaderPath) {

        std::string contents;
        std::ifstream file(pShaderPath, std::ios::in);
        if (file.is_open()) {
            std::cout << "Reading shader file... " << pShaderPath << std::endl;
            std::string line = "";
            while (getline(file, line)) contents += "\n" + line;
            file.close();
        } else {
            std::cout << "Error reading shader " << pShaderPath << std::endl;
            contents = "";
        }
        return contents;
    }

// compile the code, and detect errors.
    GLuint ShaderProgram::compileShader(GLuint pShaderType, const std::string& pShaderSource) {

        std::cout << "Compiling shader... " << std::endl;
        const char* sourcePointer = pShaderSource.c_str();
        GLuint shaderId = glCreateShader(pShaderType);
        glShaderSource(shaderId, 1, &sourcePointer, NULL);
        glCompileShader(shaderId);

        GLint compilerResult = GL_FALSE;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilerResult);

        if (compilerResult) {
            std::cout << "Shader compiled ok." << std::endl;
            return shaderId;
        } else { // get error message
            std::cout << "Shader error:" << std::endl;
            int infoLogLength;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
            char* errorMessage = new char[infoLogLength + 1];
            glGetShaderInfoLog(shaderId, infoLogLength, NULL, errorMessage);
            std::cout << errorMessage << std::endl << std::endl;
            delete[] errorMessage;
            return 0;
        }
    }
}
