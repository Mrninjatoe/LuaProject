#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "script.hpp"

class Entity {
public:
	Entity();
	virtual ~Entity();
	virtual void loadTexture(SDL_Renderer* renderer, const std::string& filePath) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void registerLuaFuncs() = 0;
	void draw(SDL_Renderer* renderer);
	const float getX() { return destination.x; }
	const float getY() { return destination.y; }
	void setPosition(const float x, const float y) { destination.x = x, destination.y = y; }
	void takeDamage(float dmg) {
		health -= dmg;
		script.push(health).setGlobal("health");
	}
	// Lua functions for all entities
	static int lua_getEntitiesAround(lua_State* lua);
	static int lua_makeDead(lua_State* lua);
protected:
	SDL_Texture* texture;
	SDL_Rect source;
	SDL_Rect destination;
	Script script;
	float posX;
	float posY;
	float health;
	float damage;
private:

};
