#pragma once
#include <memory>
#include <vector>
#include <SDL2\SDL.h>
#include "room.hpp"

class LevelEditor {
public:
	LevelEditor(SDL_Window* mainWindow);
	virtual ~LevelEditor() {};
	void _initWorld();
	void update(float delta);
private:
	std::vector<std::shared_ptr<Room>> _rooms;
	SDL_Surface* _editorSurface;
	SDL_Window* _window;
};