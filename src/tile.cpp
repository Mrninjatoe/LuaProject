#include "tile.hpp"

Tile::Tile() {
	_collidable = false;
}

Tile::Tile(SDL_Renderer* renderer, const std::string& filePath, bool collidable, int size, int x, int y) {
	script.doFile("assets/scripts/tile.lua").openLibs();
	script.push(x).setGlobal("posX");
	script.push(y).setGlobal("posY");
	_collidable = collidable;
	posX = x;
	posY = y;

	source.x = 0;
	source.y = 0;
	source.h = size;
	source.w = size;

	script.getGlobal("posX").pop(destination.x);
	script.getGlobal("posY").pop(destination.y);
	destination.h = size;
	destination.w = size;
	loadTexture(renderer, filePath);
	registerLuaFuncs();
}

Tile::~Tile() {

}

void Tile::update(float deltaTime) {

}

void Tile::registerLuaFuncs() {

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
