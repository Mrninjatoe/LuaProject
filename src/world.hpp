#pragma once
#include <memory>
#include <vector>
#include "entity.hpp"
#include "tile.hpp"

class World {
public:
	World();
	virtual ~World();
	void update(float delta);
	void drawEntities(SDL_Renderer* renderer);
private:
	std::vector<std::shared_ptr<Entity>> _entities;
};