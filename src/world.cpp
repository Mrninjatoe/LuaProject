#include "world.hpp"
#include "engine.hpp"
#include <algorithm>

World::World() {
	_currRoom = std::make_shared<Room>();
}

World::~World() {
	
}

void World::update(float delta) {
	_currRoom->update(delta);
}

void World::drawEntities(SDL_Renderer* renderer) {
	_currRoom->draw(renderer);
}