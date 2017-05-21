#pragma once
#include "entity.hpp"
#include <memory>


class Room {
public:
	Room(const std::string& file);
	~Room();
	void update(float deltaTime);
	void draw(SDL_Renderer* renderer);
	std::vector<std::shared_ptr<Entity>> getEntities() { return _entities; }
	std::vector<std::shared_ptr<Entity>> getTiles() { return _tiles; }
private:
	std::vector<std::shared_ptr<Entity>> _entities;
	std::vector<std::shared_ptr<Entity>> _tiles;
};
