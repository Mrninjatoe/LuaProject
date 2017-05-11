#include "world.hpp"
#include "engine.hpp"

World::World() {
	_createWorld();
}

World::~World() {
	
}

void World::update(float delta) {
	for (std::shared_ptr<Entity> entity : _world) {
		entity->update(delta);
	}
	for (std::shared_ptr<Entity> entity : _entities) {
		entity->update(delta);
	}
}

void World::drawEntities(SDL_Renderer* renderer) {
	for (std::shared_ptr<Entity> entity : _world) {
		entity->draw(renderer);
	}
	for (std::shared_ptr<Entity> entity : _entities) {
		entity->draw(renderer);
	}
}

void World::_createWorld() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			_world.push_back(std::make_shared<Tile>(Engine::getInstance().getRenderer(), 
				"assets/textures/dirt_block_outline.png", 
				false,
				32, i * 32, j * 32));
		}
	}
	_entities.push_back(std::make_shared<Player>(Engine::getInstance().getRenderer(),
		"assets/textures/player.png",
		32, 32 * 10, 32 * 10));
}