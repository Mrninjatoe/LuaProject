#include "player.hpp"

Player::Player() {
	
}

Player::Player(SDL_Renderer* renderer, const std::string& filePath, int size, int x, int y) {
	_inputs = std::make_shared<PlayerInput>();
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

Player::~Player() {
	
}

void Player::update(float deltaTime) {
	_inputs->update(this, deltaTime);
}

void Player::loadTexture(SDL_Renderer* renderer, const std::string& filePath) {
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
