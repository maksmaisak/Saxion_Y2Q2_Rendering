#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include "engine/core/Texture.hpp"
#include "Texture.hpp"

Texture::Texture(const std::string& filename, GLint internalFormat) {

    // Load from file and store in cache
    sf::Image image;
    if (!image.loadFromFile(filename))
        return;

    // Normal image 0,0 is top left, but opengl considers 0,0 to be bottom left, so we flip the image internally
    image.flipVertically();

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    {
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
	glDeleteTextures(1, &m_id);
}

GLuint Texture::getId() {
	return m_id;
}

bool Texture::isValid() {
    return m_id == 0;
}










