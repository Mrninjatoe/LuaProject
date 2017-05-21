#include "room.hpp"
#include "tile.hpp"
#include "engine.hpp"
#include <algorithm>

Room::Room() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (j % 5 == 0 && i % 5 == 0)
				_tiles.push_back(std::make_shared<Tile>(Engine::getInstance().getRenderer(),
					"assets/textures/stone_block_outline.png",
					true,
					32, i * 32, j * 32));
			else
				_tiles.push_back(std::make_shared<Tile>(Engine::getInstance().getRenderer(),
					"assets/textures/dirt_block_outline.png",
					false,
					32, i * 32, j * 32));
		}
	}
	_entities.push_back(std::make_shared<Player>(Engine::getInstance().getRenderer(),
		"assets/textures/player.png",
		32, 32 * 2, 32 * 1, 5, 2));
	_entities.push_back(std::make_shared<Enemy>(Engine::getInstance().getRenderer(),
		"assets/textures/enemy.png",
		32, 32 * 10, 32 * 16, 2, 1));
}

Room::~Room() {
	
}

void Room::update(float deltaTime) {

	for (std::shared_ptr<Entity> entity : _tiles) {
		entity->update(deltaTime);
	}
	for (std::shared_ptr<Entity> entity : _entities) {
		entity->update(deltaTime);
	}

	_entities.erase(std::remove_if(_entities.begin(), _entities.end(),
		[&](const std::shared_ptr<Entity>& e) -> bool {
		if (e.get()->isDead())
			return true;
		else
			return false;
	}),
		_entities.end());
}

void Room::draw(SDL_Renderer* renderer) {
	for (std::shared_ptr<Entity> entity : _tiles) {
		entity->draw(renderer);
	}
	for (std::shared_ptr<Entity> entity : _entities) {
		entity->draw(renderer);
	}
}