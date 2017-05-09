#pragma once
#include <SDL2\SDL.h>
#include <string>
#include <vector>

class Engine {
public:
	Engine();
	virtual ~Engine() {};
	void _init();
	void _initVariables();
	void _initSDL();
	void _initWorld();
	void _run();

private:
	int _width;
	int _height;
	int _fps;

	bool _quit;
	bool _vsync;

	SDL_Event _event;
	SDL_Texture* _quad;
	SDL_Window* _gWindow;
	SDL_Renderer* _gRenderer;
};