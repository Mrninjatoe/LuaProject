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
				static_cast<Player*>(player)->move(-32, 0);
				break;
			case SDL_SCANCODE_RIGHT:
				static_cast<Player*>(player)->move(32, 0);
				break;
			case SDL_SCANCODE_UP:
				static_cast<Player*>(player)->move(0, -32);
				break;
			case SDL_SCANCODE_DOWN:
				static_cast<Player*>(player)->move(0, 32);
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}