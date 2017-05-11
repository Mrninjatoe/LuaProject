#pragma once
#include "entity.hpp"

class Tile : public Entity{
public:
	Tile();
	Tile(SDL_Renderer* renderer, const std::string& filePath, bool collidable, int size, int x, int y);
	virtual ~Tile();
	virtual void loadTexture(SDL_Renderer* renderer, const std::string& filePath);
	virtual void update(float deltaTime);
private:
	bool _collidable;
};