#pragma once
#include <memory>
#include <vector>
#include "entity.hpp"
#include "tile.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "room.hpp"

class World {
public:
	World();
	virtual ~World();
	void update(float delta);
	void drawEntities(SDL_Renderer* renderer);
	std::shared_ptr<Entity> getPlayer() { 
		for (std::shared_ptr<Entity> entity : _currRoom->getEntities()) {
			if (std::static_pointer_cast<Player>(entity) != nullptr)
				return entity;
		}
	}
	std::vector<std::shared_ptr<Entity>> getEntities() { return _currRoom->getEntities(); }
	std::vector<std::shared_ptr<Entity>> getWorld() { return _currRoom->getTiles(); }
private:
	std::shared_ptr<Room> _currRoom;
	bool playerDead;
};