#pragma once
#include "entity.hpp"
#include <memory>

class Enemy : public Entity {
public:
	Enemy();
	Enemy(SDL_Renderer* renderer, const std::string& filePath, int size, int x, int y, float hp, float dmg);
	virtual ~Enemy();
	virtual void loadTexture(SDL_Renderer* renderer, const std::string& filePath);
	virtual void update(float deltaTime);
	virtual void registerLuaFuncs();
	static int lua_move(lua_State* lua);
	static int lua_attackPlayer(lua_State* lua);
private:

};
