#include "room.hpp"
#include "player.hpp"

Room::Room() {
	//int iOffset = 14;
	//int jOffset = 14;
	//_tiles.resize(29);
	//
	//for (int i = 0; i < 29; i++) {
	//	for (int j = 0; j < 29; j++) {
	//		_tiles.at(i).push_back(std::make_shared<Tile>(glm::vec3(i - iOffset, j - jOffset, 0), false));
	//		_entities.push_back(_tiles.at(i).at(j));
	//	}
	//}
	//_player = std::make_shared<Player>(glm::vec3(0));
}

Room::~Room() {
	
}

void Room::update(float delta) {
	for (std::shared_ptr<Entity> entity : _entities) {
		entity->update(delta);
	}
}

std::vector<std::shared_ptr<Entity>>& Room::getEntities() {
	return _entities;
}

std::shared_ptr<Entity>& Room::getPlayer() {
	return _player;
}