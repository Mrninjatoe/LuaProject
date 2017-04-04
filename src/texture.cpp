#include "texture.hpp"
#include "SDL2\SDL.h"
#include "SDL2\SDL_image.h"

Texture::Texture(const std::string& textureName) {
	// Load in image with SDL
	SDL_Surface* image = IMG_Load(textureName.c_str());
	if (image == NULL)
		printf("Failed to load image %s! SDL_image Error: %s", textureName.c_str(), IMG_GetError());

	// Format is always going to be RGB.
	GLenum format = GL_RGB;

	_createTexture(format, image->w, image->h, image->pixels);
}

void Texture::_createTexture(GLenum format, GLuint w, GLuint h, const void* pixels) {
	// Create texture with the image's pixel data.
	glGenTextures(1, &_texture);
	glActiveTexture(GL_TEXTURE0); // Increases the number of textures by one.

	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexImage2D(
		GL_TEXTURE_2D, 0, format, 
		w, h, 0, format, 
		GL_UNSIGNED_BYTE, pixels
	);
}