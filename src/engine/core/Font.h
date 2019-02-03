//
// Created by Maksym Maisak on 2019-02-03.
//

#ifndef SAXION_Y2Q2_RENDERING_FONT_H
#define SAXION_Y2Q2_RENDERING_FONT_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include <GL/glew.h>
#include "glm.hpp"
#include <unordered_map>
#include <memory>
#include "ShaderProgram.hpp"

namespace en {

    class Font {

    public:

        struct Character {
            GLuint textureId;   // ID handle of the glyph texture
            glm::ivec2 size;    // Size of glyph
            glm::ivec2 bearing; // Offset from baseline to left/top of glyph
            FT_Pos advance;     // Horizontal offset to advance to next glyph
        };

        Font(const std::string& filename);
        ~Font();

        void render(const std::string& text, glm::vec<2, GLfloat> pos = {0, 0}, GLfloat scale = 1.f, const glm::mat4& projection = glm::ortho(0, 1, 0, 1));

    private:

        std::shared_ptr<ShaderProgram> m_shader;

        FT_Face m_face = nullptr;
        std::unordered_map<GLchar, Character> m_characters;
        GLuint m_vao = 0;
        GLuint m_vbo = 0;
    };
}

#endif //SAXION_Y2Q2_RENDERING_FONT_H
