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
		case SDL_QUIT:
			Engine::getInstance().setQuit(true);
			break;
		case SDL_KEYDOWN:
			switch (_event.key.keysym.scancode) {
			case SDL_SCANCODE_LEFT:
				player->move(-32, 0);
				break;
			case SDL_SCANCODE_RIGHT:
				player->move(32, 0);
				break;
			case SDL_SCANCODE_UP:
				player->move(0, -32);
				break;
			case SDL_SCANCODE_DOWN:
				player->move(0, 32);
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}