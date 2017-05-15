#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "script.hpp"

class Entity {
public:
	Entity();
	virtual ~Entity();
	virtual void loadTexture(SDL_Renderer* renderer, const std::string& filePath) = 0;
	virtual void update(float deltaTime) = 0;

	virtual void move(float x, float y);
	void draw(SDL_Renderer* renderer);
protected:
	SDL_Texture* texture;
	SDL_Rect* source;
	SDL_Rect* destination;
	float posX, posY;
	Script script;
private:

};