#include "playerinput.hpp"
#include "engine.hpp"

PlayerInput::PlayerInput() {
	
}

PlayerInput::~PlayerInput() {
	
}

void PlayerInput::update(Entity* player, float deltaTime) {
	while (SDL_PollEvent(&_event)) {
		switch (_event.type)
		{
		// This quit is a hack.
		case SDL_QUIT:
			Engine::getInstance().setQuit(true);
			break;
		case SDL_KEYDOWN:
			switch (_event.key.keysym.scancode) {
			case SDL_SCANCODE_LEFT:
				key = left;
				break;
			case SDL_SCANCODE_RIGHT:
				key = right;
				break;
			case SDL_SCANCODE_UP:
				key = up;
				break;
			case SDL_SCANCODE_DOWN:
				key = down;
				break;
			case SDL_SCANCODE_F:
				key = shoot;
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}