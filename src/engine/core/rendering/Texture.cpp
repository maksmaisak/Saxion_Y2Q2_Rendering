#include <iostream>
#include <string>

#include "Texture.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "glm.hpp"
#include "GLHelpers.h"

namespace {

    int getNumMipmaps(Texture::Size size) {

        int i = 1;
        while (true) {
            size.x = std::max(1, size.x / 2);
            size.y = std::max(1, size.y / 2);
            if (size.x == 1 && size.y == 1)
                break;

            ++i;
        }

        return i;
    }
}

Texture::Texture(const std::string& filename, GLint internalFormat) {

    // Load from file using sf::Image, then put the data in an opengGL buffer.

    sf::Image image;
    if (!image.loadFromFile(filename))
        return;

    auto temp = image.getSize();
    m_size = {temp.x, temp.y};

    // 0,0 in sf::Image is top left, but opengl considers 0,0 to be bottom left, flip to compensate.
    image.flipVertically();

    glCheckError();
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_size.x, m_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
	glDeleteTextures(1, &m_id);
}

GLuint Texture::getId() const {
	return m_id;
}

bool Texture::isValid() const {
    return m_id != 0;
}

Texture::Size Texture::getSize() const {
    return m_size;
}










