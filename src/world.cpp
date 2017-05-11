#include "world.hpp"
#include "engine.hpp"

World::World() {
	_createWorld();
}

World::~World() {
	
}

void World::update(float delta) {
	for (std::shared_ptr<Entity> entity : _entities) {
		entity->update(delta);
	}
	for (std::shared_ptr<Entity> entity : _world) {
		entity->update(delta);
	}
}

void World::drawEntities(SDL_Renderer* renderer) {
	for (std::shared_ptr<Entity> entity : _entities) {
		entity->draw(renderer);
	}
	for (std::shared_ptr<Entity> entity : _world) {
		entity->draw(renderer);
	}
}

void World::_createWorld() {
	for (int i = 0; i < 34; i++) {
		for (int j = 0; j < 34; j++) {
			_world.push_back(std::make_shared<Tile>(Engine::getInstance().getRenderer(), 
				"assets/textures/environment_block.png", 
				false, 
				25, i * 25, j * 25));
		}
	}
}