#include "engine.hpp"
#include <SDL2/SDL_image.h>
#include <cstdlib>

// Each room has a orthographic view with the size of -15 to 15 in x and y direction
// Each block represents two digits in this space.
// Player and NPC to be decided...

Engine::~Engine() {
	SDL_DestroyRenderer(_gRenderer);
	SDL_DestroyWindow(_gWindow);

	IMG_Quit();
	SDL_Quit();
}

int Engine::run() {
	_init();
	uint32_t lastTime = SDL_GetTicks();
	while (!_quit) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				Engine::getInstance().setQuit(true);
				break;
			default:
				break;
			}
		}

		uint32_t curTime = SDL_GetTicks();
		float delta = (curTime - lastTime) / 1000.0f;
		lastTime = curTime;

		SDL_RenderClear(_gRenderer);
		_world->update(delta);
		_world->drawEntities(_gRenderer);
		SDL_RenderPresent(_gRenderer);
	}
	return 0;
}

void Engine::_init() {
	_initVariables();
	_initSDL();
	_initWorld();
}

void Engine::_initVariables() {
	_vsync = true;
	_quit = false;

	_width = 640;
	_height = 640;
}

void Engine::endGame(const std::string& text) {
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game has ended..", text.c_str(), _gWindow);
	_quit = true;
	exit(0);
}

void Engine::_initWorld() {
	_world = std::make_shared<World>();
}

void Engine::_initSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		printf("Failed to intialize SDL, SDL_Error: %s\n", SDL_GetError());
	else {
		_gWindow = SDL_CreateWindow("LuaProject", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_SHOWN);

		if (_gWindow == NULL)
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		else {
			_gRenderer = SDL_CreateRenderer(_gWindow, -1, SDL_RENDERER_ACCELERATED);

			if (_gRenderer == NULL)
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
			else {
				SDL_SetRenderDrawColor(_gRenderer, 0, 0, 0, 1);
				if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
					printf("Failed to load SDL_Image.\n");
			}
		}
	}
}
