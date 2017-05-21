#pragma once
#include <memory>
#include "entity.hpp"
#include "script.hpp"

class Room {
public:
	Room(const std::string& file);
	~Room();
	void update(float deltaTime);
	void draw(SDL_Renderer* renderer);
	std::vector<std::shared_ptr<Entity>> getEntities() { return _entities; }
	std::vector<std::shared_ptr<Entity>> getTiles() { return _tiles; }
	static int lua_endGame(lua_State* lua);
private:
	std::vector<std::shared_ptr<Entity>> _entities;
	std::vector<std::shared_ptr<Entity>> _tiles;
	Script _script;
};
