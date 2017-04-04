#include "entitymanager.hpp"

EntityManager::EntityManager() {
	_entities.push_back(std::make_shared<Player>());
}

void EntityManager::_updateEntities() {
	for (std::shared_ptr<Entity> entity : _entities) {
		entity->update();
	}
}

void EntityManager::_renderEntities(std::shared_ptr<ShaderProgram>& shader) {
	for (std::shared_ptr<Entity> entity : _entities) {
		shader->addUniform("m", entity->getModel());
		entity->render();
	}
}

void EntityManager::addNPC() {
	//_initNPCScript("assets/scripts/world_NPCs");
}