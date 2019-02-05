//
// Created by Maksym Maisak on 2019-02-03.
//

#include "Font.h"
#include <optional>

using namespace en;

/// A RAII wrapper around a FT_Library
class FreeFontLibrary {

public:

    inline FreeFontLibrary() {

        if (FT_Init_FreeType(&library))
            std::cerr << "Freetype: Could not initialize a FreeType Library." << std::endl;
    }

    inline ~FreeFontLibrary() {

        if (library)
            FT_Done_FreeType(library);
    }

    inline operator FT_Library&() {
        return library;
    }

private:

    FT_Library library = nullptr;
};

FT_Library& getFreeTypeLibrary() {

    static FreeFontLibrary library;
    return library;
}

std::optional<Font::Character> loadCharacter(FT_Face& face, FT_ULong charCode) {

    if (FT_Load_Char(face, charCode, FT_LOAD_RENDER)) {
        std::cout << "Freetype: Failed to load a glyph" << std::endl;
        return std::nullopt;
    }

    // Generate texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        face->glyph->bitmap.width,
        face->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        face->glyph->bitmap.buffer
    );

    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return std::make_optional<Font::Character>({
        texture,
        { face->glyph->bitmap.width, face->glyph->bitmap.rows },
        { face->glyph->bitmap_left , face->glyph->bitmap_top  },
        face->glyph->advance.x
    });
}

Font::Font(const std::string& filename) : m_shader(Resources<ShaderProgram>::get("text")) {

    // Load font as face
    if (FT_New_Face(getFreeTypeLibrary(), filename.c_str(), 0, &m_face)) {
        std::cerr << "Freetype: Failed to load a font" << std::endl;
        return;
    }

    // Set size to load glyphs as
    FT_Set_Pixel_Sizes(m_face, 0, 48);

    // Preload the first 128 ASCII characters
    for (FT_ULong c = 0; c < 128; ++c) {

        std::optional<Character> character = loadCharacter(m_face, c);
        if (character)
            m_characters.emplace(c, *character);
    }

    // Set up the buffer and the vao
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo); // This buffer will contain the vertex positions and uvs for one quad
    glBindVertexArray(m_vao);
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    glBindVertexArray(0);
}

Font::~Font() {

    // TODO delete textures, vao, vbo, font face.
}

// TODO This renders each character in a separate draw call, with each character having its own thing. Use a texture atlas instead and do one draw call per text.
void Font::render(const std::string& text, glm::vec<2, GLfloat> pos, GLfloat scale, const glm::mat4& projection) {
    
    // Activate corresponding render state
    m_shader->use();

    glUniform3f(m_shader->getUniformLocation("textColor"), 1.f, 1.f, 1.f);
    glUniformMatrix4fv(m_shader->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_vao);

    for (char c : text) {

        Character& character = m_characters[c];

        GLfloat posx = pos.x + character.bearing.x * scale;
        GLfloat posy = pos.y - (character.size.y - character.bearing.y) * scale;

        GLfloat w = character.size.x * scale;
        GLfloat h = character.size.y * scale;

        // Bind this character's texture
        glBindTexture(GL_TEXTURE_2D, character.textureId);

        // Define the quad for this character
        GLfloat vertices[6][4] = {
            {posx,     posy + h, 0.0, 0.0},
            {posx,     posy,     0.0, 1.0},
            {posx + w, posy,     1.0, 1.0},

            {posx,     posy + h, 0.0, 0.0},
            {posx + w, posy,     1.0, 1.0},
            {posx + w, posy + h, 1.0, 0.0}
        };
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Render the quad
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        pos.x += (character.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
