#pragma once
#include "entity.hpp"
#include <vector>
#include <memory>

class Tile : public Entity
{
public:
	Tile(glm::vec3 pos, bool collision);
	virtual ~Tile() {};
	virtual void update(float delta);
	virtual glm::mat4 getModel() const;
	virtual void move(glm::vec3 dir);
private:
	bool _collision;
	glm::vec3 _color;
	glm::vec3 _pos;
};