#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <map>
#include <string>
#include <GL/glew.h>
#include "glm.hpp"

/// A wrapper around a texture id.
/// Manages the lifetime of said id.
class Texture final {

public:

	using Size = glm::vec<2, GLsizei>;

	Texture(const std::string& path, GLint internalFormat = GL_SRGB_ALPHA);
	~Texture();
	Texture(const Texture&) = delete;
	Texture(Texture&&) = delete;
	Texture& operator=(const Texture&) = delete;
	Texture& operator=(Texture&&) = delete;

	GLuint getId() const;
	bool isValid() const;
	Size getSize() const;

private:

	//OpenGL id for texture buffer
	GLuint m_id = 0;
	Size m_size;
};

#endif // TEXTURE_HPP
