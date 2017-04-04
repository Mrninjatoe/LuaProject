#pragma once
#include <vector>
#include <memory>
#include "entity.hpp"
#include "shaderprogram.hpp"
#include "player.hpp"
#include "npcscript.hpp"
#include "room.hpp"

enum MOVEINPUT {LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3};

class EntityManager {
public:	
	EntityManager();
	virtual ~EntityManager() {};
	void _updateEntities(std::shared_ptr<Room> &currRoom, float delta);
	void _renderEntities(std::shared_ptr<ShaderProgram>& shader);
	void moveEntity(const MOVEINPUT dir);
	void addNPC();
private:
	std::vector<std::shared_ptr<Entity>> _entities; // Removal imminent
	std::shared_ptr<NPCScript> _npcScript;
	std::shared_ptr<Room> _currRoom;
	std::shared_ptr<Entity> _player;
};