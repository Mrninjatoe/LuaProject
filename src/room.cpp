#include "room.hpp"
#include "tile.hpp"
#include "engine.hpp"
#include <algorithm>

#include <cstdio>

Room::Room(const std::string& file) {
	FILE* fp = fopen(file.c_str(), "rb");

	char line[21] = {0};

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
				goto default_tile;

			default:
			default_tile: // NOTE! This is a goto label
				_tiles.push_back(std::make_shared<Tile>(Engine::getInstance().getRenderer(), "assets/textures/dirt_block_outline.png", false, 32, x, y));
				break;
			}
		}
	}

	fclose(fp);
}

Room::~Room() {}

void Room::update(float deltaTime) {
	for (std::shared_ptr<Entity> entity : _tiles) {
		entity->update(deltaTime);
	}
	for (std::shared_ptr<Entity> entity : _entities) {
		entity->update(deltaTime);
	}
	if (Engine::getInstance().getWorld()->getPlayer()->isDead())
		Engine::getInstance().endGame();

	_entities.erase(std::remove_if(_entities.begin(), _entities.end(), [&](const std::shared_ptr<Entity>& e) { return e.get()->isDead(); }), _entities.end());
}

void Room::draw(SDL_Renderer* renderer) {
	for (std::shared_ptr<Entity> entity : _tiles) {
		entity->draw(renderer);
	}
	for (std::shared_ptr<Entity> entity : _entities) {
		entity->draw(renderer);
	}
}
