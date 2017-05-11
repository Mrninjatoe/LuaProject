#pragma once
#include "entity.hpp"
#include <SDL2/SDL_image.h>

class Tile : public Entity{
public:
	Tile();
	Tile(SDL_Renderer* renderer, const std::string& filePath, bool collidable, int size, int x, int y);
	virtual ~Tile();
	virtual void loadTexture(SDL_Renderer* renderer, const std::string& filePath);
	virtual void move(float x = 0, float y = 0);
	virtual void update(float deltaTime);
private:
	bool _collidable;
};