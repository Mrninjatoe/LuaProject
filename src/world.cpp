#include "world.hpp"
#include "engine.hpp"
#include <algorithm>

World::World() {
	_rooms.push_back(std::make_shared<Room>("assets/maps/main.txt"));
	_currRoom = 0;
	_rooms.push_back(std::make_shared<Room>("assets/maps/roomOfDoom.txt"));
}

World::~World() {

}

void World::nextRoom() {
	_currRoom++;
	if (_currRoom == _rooms.size()) {
		Engine::getInstance().endGame("You won!");
		_currRoom = 0;
	}

}

void World::update(float delta) {
	_rooms[_currRoom]->update(delta);
}

void World::drawEntities(SDL_Renderer* renderer) {
	_rooms[_currRoom]->draw(renderer);
}
