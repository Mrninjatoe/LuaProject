#pragma once
#include "entity.hpp"
#include "texture.hpp"
#include <memory>
#include "script.hpp"

class Player : public Entity {
public:
	Player(glm::vec3 pos);
	Player();
	virtual ~Player() {};
	virtual void update(float delta);
	virtual glm::mat4 getModel() const;
	virtual void move(glm::vec3 dir);
private:
	int _hp;
	glm::vec3 _pos;
};