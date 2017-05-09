#include "engine.hpp"
#include <SDL2\SDL_image.h>

// Each room has a orthographic view with the size of -15 to 15 in x and y direction
// Each block represents two digits in this space.
// Player and NPC to be decided...

Engine::Engine(){
	_init();
	_run();
}

void Engine::_run() {
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	float deltaTime = 0;

	while (!_quit) {
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = (float)((NOW - LAST) * 1000 / SDL_GetPerformanceCounter());
		while (SDL_PollEvent(&_event)) {
			switch (_event.type)
			{
			case SDL_QUIT:
				_quit = true;
				break;
			case SDL_KEYDOWN:
				switch (_event.key.keysym.scancode)
				{
				case SDL_SCANCODE_LEFT:
					break;
				case SDL_SCANCODE_RIGHT:
					break;
				case SDL_SCANCODE_UP:
					break;
				case SDL_SCANCODE_DOWN:
					break;
				default:
					break;
				}
			default:
				break;
			}
		}

		SDL_RenderClear(_gRenderer);
		//SDL_RenderCopy(gRender, gTexture, NULL, NULL);
		SDL_RenderPresent(_gRenderer);
	}
	SDL_Quit();
}

void Engine::_init() {
	_initVariables();
	_initSDL();
	_initWorld();
}

void Engine::_initVariables() {
	_vsync = true;
	_quit = false;

	_width	= 880;
	_height	= 880;
}

void Engine::_initWorld() {

}

void Engine::_initSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		printf("Failed to intialize SDL, SDL_Error: %s\n", SDL_GetError());
	else {
		_gWindow = SDL_CreateWindow(
			"LuaProject",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			_width,
			_height,
			SDL_WINDOW_SHOWN
		);

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
