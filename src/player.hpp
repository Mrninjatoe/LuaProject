#pragma once
#include "entity.hpp"
#include "texture.hpp"
#include <memory>
#include "script.hpp"

class Player : public Entity {
public:
	Player();
	virtual ~Player() {};
	virtual void update();
	virtual void _fixBuffers();
	virtual void _fixVertAttributes();
	virtual glm::mat4 getModel() const;
private:
	std::shared_ptr<Texture> _texture;
	int _hp;
};