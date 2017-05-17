#include "entity.hpp"
#include "tile.hpp"
#include "engine.hpp"
#include <cmath>

Entity::Entity() {
	lua_register(script.getState(), "getEntitiesAround", lua_getEntitiesAround);
}

Entity::~Entity() {
	delete[] source;
	delete[] destination;
}

void Entity::draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, source, destination);
}

int Entity::lua_getEntitiesAround(lua_State* lua) {
	int n = lua_gettop(lua);
	auto world = Engine::getInstance().getWorld()->getWorld();
	auto entities = Engine::getInstance().getWorld()->getEntities();
	float x = lua_tonumber(lua, 1);
	float y = lua_tonumber(lua, 2);
	lua_createtable(lua, 0, 16);
	int i = 0;
	for (std::shared_ptr<Entity> entity : world) {
		auto tile = std::dynamic_pointer_cast<Tile>(entity);
		if (tile != nullptr) {
			float tempX = x - tile->destination->x;
			float tempY = y - tile->destination->y;
			float distance = sqrt(pow(tempX, 2) + pow(tempY, 2));
			if (tile->getCollidable() && distance <= 46) {
				lua_pushnumber(lua, i);
				lua_pushnumber(lua, tile->destination->x);
				lua_settable(lua, -3);
				i++;
				lua_pushnumber(lua, i);
				lua_pushnumber(lua, tile->destination->y);
				lua_settable(lua, -3);
				i++;
			}
		}
	}
	for (std::shared_ptr<Entity> entity : entities) {
		auto enemy = std::dynamic_pointer_cast<Enemy>(entity);
		if (enemy != nullptr) {
			float tempX = x - enemy->destination->x;
			float tempY = y - enemy->destination->y;
			float distance = sqrt(pow(tempX, 2) + pow(tempY, 2));
			if (distance <= 46) {
				lua_pushnumber(lua, i);
				lua_pushnumber(lua, enemy->destination->x);
				lua_settable(lua, -3);
				i++;
				lua_pushnumber(lua, i);
				lua_pushnumber(lua, enemy->destination->y);
				lua_settable(lua, -3);
				i++;
			}
		}
	}
	return 1;
}
