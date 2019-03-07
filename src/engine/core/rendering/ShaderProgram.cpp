#include <iostream>
#include <fstream>
#include <optional>
#include "ShaderProgram.hpp"
#include "GLHelpers.h"

using namespace en;

namespace {

    std::optional<std::string> readFile(const std::string& pShaderPath) {

        std::string contents;
        std::ifstream file(pShaderPath, std::ios::in);
        if (!file.is_open()) {
            std::cout << "Error reading shader " << pShaderPath << std::endl;
            return std::nullopt;
        }

        std::cout << "Reading shader file... " << pShaderPath << std::endl;
        std::string line;
        while (getline(file, line))
            contents += "\n" + line;
        file.close();

        return contents;
    }

    void printProgramError(GLuint programId) {

        int infoLogLength;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
        auto errorMessage = std::make_unique<char[]>(infoLogLength + 1);

        glGetProgramInfoLog(programId, infoLogLength, nullptr, errorMessage.get());
        std::cerr << errorMessage.get() << std::endl << std::endl;
    }
}

ShaderProgram::ShaderProgram() {

    m_programId = glCreateProgram();
    std::cout << std::endl << "Program created with id:" << m_programId << std::endl;
}

ShaderProgram::~ShaderProgram() {

    glDeleteProgram(m_programId);
}

bool ShaderProgram::addShader(GLuint shaderType, const std::string& filepath) {

    std::optional<std::string> shaderCode = readFile(filepath);
    if (!shaderCode)
        return false;

    GLuint shaderId = compileShader(shaderType, *shaderCode);
    if (shaderId == 0)
        return false;

    m_shaderIds.push_back(shaderId);
    return true;
}

void ShaderProgram::finalize() {

    for (GLuint shaderId : m_shaderIds)
        glAttachShader(m_programId, shaderId);
    glLinkProgram(m_programId);

    // Check the program
    GLint didLinkSuccessfully = GL_FALSE;
    glGetProgramiv(m_programId, GL_LINK_STATUS, &didLinkSuccessfully);

    if (didLinkSuccessfully) {

        std::cout << "Program linked ok." << std::endl << std::endl;

    } else {

        std::cerr << "Program linkage error:" << std::endl;
        printProgramError(m_programId);
    }

    for (GLuint shaderId : m_shaderIds) {
        glDeleteShader(shaderId);
    }
}

void ShaderProgram::use() {

    glUseProgram(m_programId);
}

GLint ShaderProgram::getUniformLocation(const std::string& pName) {

    return glGetUniformLocation(m_programId, pName.c_str());
}

GLint ShaderProgram::getAttribLocation(const std::string& pName) {

    return glGetAttribLocation(m_programId, pName.c_str());
}

// compile the code, and detect errors.
GLuint ShaderProgram::compileShader(GLuint pShaderType, const std::string& pShaderSource) {

    std::cout << "Compiling shader... " << std::endl;
    const char* sourcePointer = pShaderSource.c_str();
    GLuint shaderId = glCreateShader(pShaderType);
    glShaderSource(shaderId, 1, &sourcePointer, nullptr);
    glCompileShader(shaderId);

    GLint compilerResult = GL_FALSE;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilerResult);
    if (compilerResult == GL_TRUE) {

        std::cout << "Shader compiled ok." << std::endl;
        return shaderId;
    }

    std::cout << "Shader error:" << std::endl;
    printProgramError(m_programId);
    return 0;
}

std::vector<UniformInfo> ShaderProgram::getAllUniforms() {

    std::vector<UniformInfo> vector;

    GLint count;
    glGetProgramiv(m_programId, GL_ACTIVE_UNIFORMS, &count);

    for (GLint i = 0; i < count; ++i) {

        const GLsizei nameBufferSize = 128;
        GLchar nameBuffer[nameBufferSize];
        GLsizei nameLength;
        GLint size;
        GLenum uniformType;
        glGetActiveUniform(m_programId, (GLuint)i, nameBufferSize, &nameLength, &size, &uniformType, nameBuffer);

        auto name = std::string(nameBuffer, static_cast<std::size_t>(nameLength));
        vector.push_back({getUniformLocation(name), name});
    }

    return vector;
}
