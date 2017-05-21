#include "room.hpp"
#include "tile.hpp"
#include "doortile.hpp"
#include "engine.hpp"
#include <algorithm>

#include <cstdio>

Room::Room(const std::string& file) {
	FILE* fp = fopen(file.c_str(), "rb");

	char line[21] = {0};
	int amountOfEnemies = 0;
	for (int yy = 0; yy < 20; yy++) {
		fscanf(fp, "%20s\n", line);
		for (int xx = 0; xx < 20; xx++) {
			int x = xx * 32;
			int y = yy * 32;

			switch (line[xx]) {
			// Special tiles:
			case '#':
				_tiles.push_back(std::make_shared<Tile>(Engine::getInstance().getRenderer(), "assets/textures/stone_block_outline.png", true, 32, x, y));
				break;

			// Entities with default tile:

			case 'P':
				_entities.push_back(std::make_shared<Player>(Engine::getInstance().getRenderer(), "assets/textures/player.png", 32, x, y, 5, 2));
				goto default_tile;

			case 'E':
				_entities.push_back(std::make_shared<Enemy>(Engine::getInstance().getRenderer(), "assets/textures/enemy.png", 32, x, y, 2, 1));
				amountOfEnemies++;
				goto default_tile;

			default:
			default_tile: // NOTE! This is a goto label
				_tiles.push_back(std::make_shared<Tile>(Engine::getInstance().getRenderer(), "assets/textures/dirt_block_outline.png", false, 32, x, y));
				break;
			}
		}
	}
	fclose(fp);
	
	_script.doFile("assets/scripts/room.lua").openLibs();
	_script.push(amountOfEnemies).setGlobal("amountOfEnemies");
	_script.push(this).setGlobal("userdata");
	lua_register(_script.getState(), "endGame", lua_endGame);
	lua_register(_script.getState(), "spawnDoor", lua_spawnDoor);
}

Room::~Room() {}

void Room::update(float deltaTime) {
	for (std::shared_ptr<Entity> entity : _tiles) {
		entity->update(deltaTime);
	}
	for (std::shared_ptr<Entity> entity : _entities) {
		entity->update(deltaTime);
		if (std::dynamic_pointer_cast<Player>(entity) != nullptr) {
			_script.push(entity->isDead()).setGlobal("playerIsDead");
		}
	}

	_script.getGlobal("update").push(deltaTime).call(1, 0);
	_entities.erase(std::remove_if(_entities.begin(), _entities.end(), [&](const std::shared_ptr<Entity>& e) { return e.get()->isDead(); }), _entities.end());
	_script.push((int)_entities.size() - 1).setGlobal("amountOfEnemies"); // -1 because of player
}

int Room::lua_endGame(lua_State* lua) {
	Engine::getInstance().endGame("You died!");
	return 0;
}

int Room::lua_spawnDoor(lua_State* lua) {
	auto room = (Room*)lua_touserdata(lua, 1);
	room->generateDoor();
	lua_pushnumber(lua, 19 * 32);
	lua_pushnumber(lua, 10 * 32);
	return 2;
}

void Room::generateDoor() {
	_tiles.push_back(std::make_shared<DoorTile>(Engine::getInstance().getRenderer(), "assets/textures/knas_block.png", 32, 19 * 32, 10 * 32));
}

void Room::draw(SDL_Renderer* renderer) {
	for (std::shared_ptr<Entity> entity : _tiles) {
		entity->draw(renderer);
	}
	for (std::shared_ptr<Entity> entity : _entities) {
		entity->draw(renderer);
	}
}
