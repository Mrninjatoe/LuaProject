#include "world.hpp"
#include "engine.hpp"

World::World() {
	_entities.push_back(std::make_shared<Tile>(Engine::getInstance().getRenderer(), "assets/textures/environment_block.png", false));
}

World::~World() {
	
}

void World::update(float delta) {
	for (std::shared_ptr<Entity> entity : _entities) {
		entity->update(delta);
	}
}

void World::drawEntities(SDL_Renderer* renderer) {
	for (std::shared_ptr<Entity> entity : _entities) {
		entity->draw(renderer);
	}
}