#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "world.hpp"
#include "entity.hpp"

class Engine {
public:
	static Engine& getInstance() {
		static Engine instance;
		
		return instance;
	}

	Engine(Engine const&) = delete;
	void operator=(Engine const&) = delete;
	SDL_Renderer* getRenderer() { return _gRenderer; }
	std::shared_ptr<World> getWorld() { return _world; }
	void setQuit(bool quit) { _quit = quit; }
	int run();

private:
	Engine() {};
	virtual ~Engine();
	void _init();
	void _initVariables();
	void _initSDL();
	void _initWorld();
	void _quitProgram();

	int _width;
	int _height;
	int _fps;

	bool _quit;
	bool _vsync;
	std::shared_ptr<World> _world;

	SDL_Window* _gWindow;
	SDL_Renderer* _gRenderer;
};