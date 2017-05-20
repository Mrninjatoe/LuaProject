#include "playerinput.hpp"
#include "engine.hpp"

PlayerInput::PlayerInput() {

}

PlayerInput::~PlayerInput() {

}

void PlayerInput::update(Entity* player, float deltaTime) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		// This quit is a hack.
		case SDL_QUIT:
			Engine::getInstance().setQuit(true);
			break;
		default:
			break;
		}
	}

	const Uint8* keyMap = SDL_GetKeyboardState(NULL);
	keys = 0;
	if (keyMap[SDL_SCANCODE_A] || keyMap[SDL_SCANCODE_LEFT])
		keys |= Keys::left;
	if (keyMap[SDL_SCANCODE_D] || keyMap[SDL_SCANCODE_RIGHT])
		keys |= Keys::right;
	if (keyMap[SDL_SCANCODE_W] || keyMap[SDL_SCANCODE_UP])
		keys |= Keys::up;
	if (keyMap[SDL_SCANCODE_S] || keyMap[SDL_SCANCODE_DOWN])
		keys |= Keys::down;
	if (keyMap[SDL_SCANCODE_F])
		keys |= Keys::shoot;
}
