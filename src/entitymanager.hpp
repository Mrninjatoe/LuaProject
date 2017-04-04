#pragma once
#include <vector>
#include <memory>
#include "entity.hpp"
#include "shaderprogram.hpp"
#include "player.hpp"
#include "npcscript.hpp"
class EntityManager {
public:	
	EntityManager();
	virtual ~EntityManager() {};
	void _updateEntities();
	void _renderEntities(std::shared_ptr<ShaderProgram>& shader);
	void addNPC();
private:
	std::vector<std::shared_ptr<Entity>> _entities;
	std::shared_ptr<NPCScript> _initNPCScript;
};