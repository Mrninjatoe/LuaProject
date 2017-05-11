#pragma once
#include <memory>
#include <vector>
#include "entity.hpp"
#include "tile.hpp"
#include "player.hpp"

class World {
public:
	World();
	virtual ~World();
	void update(float delta);
	void drawEntities(SDL_Renderer* renderer);
private:
	void _createWorld();
	std::vector<std::shared_ptr<Entity>> _entities;
	std::vector<std::shared_ptr<Entity>> _world;
};