#include "enemy.hpp"
#include "engine.hpp"

Enemy::Enemy() {

}

Enemy::Enemy(SDL_Renderer* renderer, const std::string& filePath, int size, int x, int y) {
	script.doFile("assets/scripts/enemy.lua").openLibs();
	script.push(x).setGlobal("posX");
	script.push(y).setGlobal("posY");
	script.push(this).setGlobal("userdata");

	source = new SDL_Rect();
	source->x = 0;
	source->y = 0;
	source->h = size;
	source->w = size;

	destination = new SDL_Rect();
	destination->h = size;
	destination->w = size;
	script.getGlobal("posX").pop(destination->x)
		.getGlobal("posY").pop(destination->y);

	loadTexture(renderer, filePath);
	registerLuaFuncs();
}

Enemy::~Enemy() {

}

void Enemy::update(float deltaTime) {
	script.getGlobal("update").push(deltaTime).call(1, 0);
}

int Enemy::lua_move(lua_State* lua) {
	Enemy* temp = (Enemy*)(lua_touserdata(lua, 3));
	temp->destination->x += lua_tonumber(lua, 1);
	temp->destination->y += lua_tonumber(lua, 2);
	temp->script.push(temp->destination->x);
	temp->script.push(temp->destination->y);
	return 2;
}

int Enemy::lua_getPlayerPos(lua_State* lua) {
	auto player = Engine::getInstance().getWorld()->getPlayer();
	lua_pushnumber(lua, player->getX());
	lua_pushnumber(lua, player->getY());
	return 2;
}

void Enemy::registerLuaFuncs() {
	lua_register(script.getState(), "move", lua_move);
	lua_register(script.getState(), "getPlayerPos", lua_getPlayerPos);
}

void Enemy::loadTexture(SDL_Renderer* renderer, const std::string& filePath) {
	SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());
	if (!loadedSurface)
		printf("Unable to load image %s! SDL_image Error: %s", filePath.c_str(), IMG_GetError());
	else {
		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (texture == NULL)
			printf("Unable to create ctexture from %s! SDL Error: %s\n", filePath.c_str(), SDL_GetError());
	}
	SDL_FreeSurface(loadedSurface);
}
