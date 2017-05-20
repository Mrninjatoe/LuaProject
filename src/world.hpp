#pragma once
#include <memory>
#include <vector>
#include "entity.hpp"
#include "tile.hpp"
#include "player.hpp"
#include "enemy.hpp"

class World {
public:
	World();
	virtual ~World();
	void update(float delta);
	void drawEntities(SDL_Renderer* renderer);
	std::shared_ptr<Entity> getPlayer() { return _entities[0]; }
	std::vector<std::shared_ptr<Entity>> getEntities() { return _entities; }
	std::vector<std::shared_ptr<Entity>> getWorld() { return _world; }
	void removeEntity(Entity* entity);
private:
	void _createWorld();
	std::vector<std::shared_ptr<Entity>> _entities;
	std::vector<std::shared_ptr<Entity>> _world;
};