#pragma once
#include "entity.hpp"
#include "playerinput.hpp"
#include <memory>

class Player : public Entity {
public:
	Player();
	Player(SDL_Renderer* renderer, const std::string& filePath, int size, int x, int y, float hp, float dmg);
	virtual ~Player();
	virtual void loadTexture(SDL_Renderer* renderer, const std::string& filePath);
	virtual void update(float deltaTime);
	virtual void registerLuaFuncs();
	static int lua_move(lua_State* lua);
	static int lua_getInputs(lua_State* lua);
	static int lua_attack(lua_State* lua);
private:
	std::shared_ptr<PlayerInput> _inputs;
};