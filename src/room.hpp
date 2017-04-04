#pragma once
#include <memory>
#include <vector>
#include "entity.hpp"
#include "texture.hpp"
#include "tile.hpp"

class Room {
public:
	Room();
	~Room();
	void update(float delta);
	std::vector<std::shared_ptr<Entity>>& getEntities();
	std::shared_ptr<Entity>& getPlayer();
private:
	std::vector<std::vector<std::shared_ptr<Entity>>> _tiles;
	std::vector<std::shared_ptr<Entity>> _entities;
	std::shared_ptr<Entity> _player;
};