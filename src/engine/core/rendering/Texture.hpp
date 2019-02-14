#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <map>
#include <string>
#include <GL/glew.h>

/// A wrapper around a texture id.
/// Manages the lifetime of said id.
class Texture final {

public:
	Texture(const std::string& path, GLint internalFormat = GL_SRGB_ALPHA);
	~Texture();
	Texture(const Texture&) = delete;
	Texture(Texture&&) = delete;
	Texture& operator=(const Texture&) = delete;
	Texture& operator=(Texture&&) = delete;

	GLuint getId();
	bool isValid();

protected:

	//OpenGL id for texture buffer
	GLuint m_id = 0;
};

#endif // TEXTURE_HPP
