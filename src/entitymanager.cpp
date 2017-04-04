#include "entitymanager.hpp"

EntityManager::EntityManager() {

}

void EntityManager::_updateEntities(std::shared_ptr<Room>& currRoom, float delta) {
	_currRoom = currRoom;
	_player = currRoom->getPlayer();
	for (std::shared_ptr<Entity> entity : _currRoom->getEntities()) {
		entity->update(delta);
		_player->update(delta);
	}
}

void EntityManager::_renderEntities(std::shared_ptr<ShaderProgram>& shader) {
	for (std::shared_ptr<Entity> entity : _currRoom->getEntities()) {
		shader->addUniform("m", entity->getModel());
		entity->render();
		shader->addUniform("m", _player->getModel());
		_player->render();
	}
}

void EntityManager::addNPC() {
	//_initNPCScript("assets/scripts/world_NPCs");
}

void EntityManager::moveEntity(const MOVEINPUT dir) {
	switch (dir)
	{
	case LEFT:
		_player->move(glm::vec3(-1, 0, 0));
		break;
	case RIGHT:
		_player->move(glm::vec3(1, 0, 0));
		break;
	case UP:
		_player->move(glm::vec3(0, -1, 0));
		break;
	case DOWN:
		_player->move(glm::vec3(0, 1, 0));
		break;
	default:
		break;
	}
}