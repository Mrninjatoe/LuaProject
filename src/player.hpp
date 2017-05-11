#pragma once
#include "entity.hpp"

class Player : public Entity {
	Player();
	virtual ~Player();
	virtual void loadTexture(SDL_Renderer* renderer, const std::string& filePath);
	virtual void move(float x, float y);
	virtual void update(float deltaTime);
};