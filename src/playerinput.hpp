#pragma once
#include <SDL2/SDL.h>
#include "entity.hpp"
#include <memory>

class PlayerInput {
public:
	enum Keys : int {
		nothing = 0,
		left = 1,
		right = 2,
		up = 4,
		down = 8,
		shoot = 16
	};
	PlayerInput();
	virtual ~PlayerInput();
	void update(Entity* player, float deltaTime);
	int getInput() { return keys; };
private:
	int keys;
};
