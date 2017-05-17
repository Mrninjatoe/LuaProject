#include "player.hpp"

Player::Player() {
	
}

Player::Player(SDL_Renderer* renderer, const std::string& filePath, int size, int x, int y) {
	_inputs = std::make_shared<PlayerInput>();

	source = new SDL_Rect();
	source->x = 0;
	source->y = 0;
	source->h = size;
	source->w = size;

	destination = new SDL_Rect();
	destination->h = size;
	destination->w = size;
	
	script.doFile("assets/scripts/player.lua").openLibs();
	script.getGlobal("posX").pop(destination->x)
		.getGlobal("posY").pop(destination->y);
	
	loadTexture(renderer, filePath);
	registerLuaFuncs();
}

Player::~Player() {
	
}

void Player::update(float deltaTime) {
	script.getGlobal("update").push(deltaTime).call(1, 0);
	_inputs->update(this, deltaTime);
}

void Player::move(float x, float y) {
	script.getGlobal("move").push(x).push(y).call(2, 2)
		.pop(destination->y).pop(destination->x);
}

void Player::attack() {
	
}

void Player::registerLuaFuncs() {

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
