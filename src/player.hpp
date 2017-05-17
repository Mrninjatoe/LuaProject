#pragma once
#include "entity.hpp"
#include "playerinput.hpp"
#include <memory>

class Player : public Entity {
public:
	Player();
	Player(SDL_Renderer* renderer, const std::string& filePath, int size, int x, int y);
	virtual ~Player();
	virtual void loadTexture(SDL_Renderer* renderer, const std::string& filePath);
	virtual void update(float deltaTime);
	virtual void registerLuaFuncs();
	virtual void move(float x, float y);
	void attack();
private:
	std::shared_ptr<PlayerInput> _inputs;
};