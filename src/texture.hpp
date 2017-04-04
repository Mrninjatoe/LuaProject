#pragma once
#include <string>
#include <glad\glad.h>

class Texture {
public:
	Texture(const std::string& textureName);
	~Texture() {};
	void _createTexture(GLenum format, GLuint w, GLuint h, const void* pixels);
private:
	GLuint _texture;
	GLint _nrOfTextures;
};