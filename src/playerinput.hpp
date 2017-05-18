#pragma once
#include <SDL2/SDL.h>
#include "entity.hpp"
#include <memory>

class PlayerInput {
public:
	enum PlayerPressed : int {nothing = 0, left = 1, right, up, down, shoot};
	PlayerInput();
	virtual ~PlayerInput();
	void update(Entity* player, float deltaTime);
	int getInput() { return key; };
	void setKeyPressed(PlayerPressed newKey) { key = newKey; }
private:
	SDL_Event _event;
	PlayerPressed key;
};