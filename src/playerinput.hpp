#pragma once
#include <SDL2/SDL.h>
#include "entity.hpp"
#include <memory>

class PlayerInput {
public:
	PlayerInput();
	virtual ~PlayerInput();
	void update(Entity* player, float deltaTime);
private:
	SDL_Event _event;
};