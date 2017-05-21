#pragma once
#include "entity.hpp"

class DoorTile : public Entity {
public:
	DoorTile();
	DoorTile(SDL_Renderer* renderer, const std::string& filePath, int size, int x, int y);
	virtual ~DoorTile();
	virtual void loadTexture(SDL_Renderer* renderer, const std::string& filePath);
	virtual void update(float deltaTime);
	virtual void registerLuaFuncs();
	static int lua_loadNewRoom(lua_State* lua);
};
