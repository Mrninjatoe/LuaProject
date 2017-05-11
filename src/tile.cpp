#include "tile.hpp"

Tile::Tile() {
	_collidable = false;
}

Tile::Tile(SDL_Renderer* renderer, const std::string& filePath, bool collidable, int size, int x, int y) {
	_collidable = collidable;
	posX = x;
	posY = y;
	source = new SDL_Rect();
	source->x = 0;
	source->y = 0;
	source->h = size;
	source->w = size;

	destination = new SDL_Rect();
	destination->x = posX;
	destination->y = posY;
	destination->h = size;
	destination->w = size;
	loadTexture(renderer, filePath);
}

Tile::~Tile() {
	delete[] source;
	delete[] destination;
}

void Tile::move(float x, float y) {
	posX += x;
	posY += y;
	destination->x = posX;
	destination->y = posY;
}

void Tile::update(float deltaTime) {
	//move(25 * deltaTime);
}

void Tile::loadTexture(SDL_Renderer* renderer, const std::string& filePath) {
	SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());
	if (!loadedSurface)
		printf("Unable to load image %s! SDL_image Error: %s", filePath.c_str(), IMG_GetError());
	else {
		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (texture == NULL)
			printf("Unable to create ctexture from %s! SDL Error: %s\n", filePath.c_str(), SDL_GetError());
	}
	SDL_FreeSurface(loadedSurface);
}