#include "entity.hpp"
#include "tile.hpp"
#include "engine.hpp"
#include <cmath>

Entity::Entity() {
	lua_register(script.getState(), "getEntitiesAround", lua_getEntitiesAround);
	lua_register(script.getState(), "makeDead", lua_makeDead);
	lua_register(script.getState(), "getPlayerPos", lua_getPlayerPos);
	dead = false;
}

Entity::~Entity() {
}

void Entity::draw(SDL_Renderer* renderer) {
	destination.x = (int)posX;
	destination.y = (int)posY;
	SDL_RenderCopy(renderer, texture, &source, &destination);
}

int Entity::lua_makeDead(lua_State* lua) {
	auto entity = (Entity*)lua_touserdata(lua, 1);
	entity->dead = true;
	return 0;
}

int Entity::lua_getEntitiesAround(lua_State* lua) {
	auto world = Engine::getInstance().getWorld()->getWorld();
	auto entities = Engine::getInstance().getWorld()->getEntities();
	float x = lua_tonumber(lua, 1);
	float y = lua_tonumber(lua, 2);
	auto self = (Entity*)lua_touserdata(lua, 3);
	lua_createtable(lua, 0, 16);
	int i = 0;
	for (std::shared_ptr<Entity> entity : world) {
		auto tile = std::dynamic_pointer_cast<Tile>(entity);
		if (tile != nullptr) {
			float tempX = x - tile->destination.x;
			float tempY = y - tile->destination.y;
			float distance = sqrt(pow(tempX, 2) + pow(tempY, 2));
			if (tile->getCollidable() && distance <= 46) {
				lua_pushnumber(lua, i);
				lua_pushnumber(lua, tile->destination.x);
				lua_settable(lua, -3);
				i++;
				lua_pushnumber(lua, i);
				lua_pushnumber(lua, tile->destination.y);
				lua_settable(lua, -3);
				i++;
			}
		}
	}
	for (std::shared_ptr<Entity> entity : entities) {
		auto enemy = std::dynamic_pointer_cast<Enemy>(entity);
		if (enemy != nullptr && entity.get() != self) {
			float tempX = x - enemy->destination.x;
			float tempY = y - enemy->destination.y;
			float distance = sqrt(pow(tempX, 2) + pow(tempY, 2));
			if (distance <= 46) {
				lua_pushnumber(lua, i);
				lua_pushnumber(lua, enemy->destination.x);
				lua_settable(lua, -3);
				i++;
				lua_pushnumber(lua, i);
				lua_pushnumber(lua, enemy->destination.y);
				lua_settable(lua, -3);
				i++;
			}
		}
	}
	return 1;
}

int Entity::lua_getPlayerPos(lua_State* lua) {
	auto player = Engine::getInstance().getWorld()->getPlayer();
	lua_pushnumber(lua, player->getX());
	lua_pushnumber(lua, player->getY());
	return 2;
}
