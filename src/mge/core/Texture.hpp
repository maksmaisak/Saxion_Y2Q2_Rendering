#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <map>
#include <string>
#include <GL/glew.h>

class Texture
{
	public:
		static Texture* load(const std::string& pTexturePath);
		virtual ~Texture();

		GLuint getId();

	protected:
	    Texture();

	    //OpenGL id for texture buffer
		GLuint _id;
};

#endif // TEXTURE_HPP
