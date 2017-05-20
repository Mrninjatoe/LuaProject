#include "player.hpp"
#include "engine.hpp"

Player::Player() {
	
}

Player::Player(SDL_Renderer* renderer, const std::string& filePath, int size, int x, int y, float hp, float dmg) {
	_inputs = std::make_shared<PlayerInput>();
	script.doFile("assets/scripts/player.lua").openLibs();
	script.push(x).setGlobal("posX")
		.push(y).setGlobal("posY");
	script.push(this).setGlobal("userdata");
	script.push(hp).setGlobal("health")
		.push(dmg).setGlobal("damage");
	
	posX = x;
	posY = y;
	health = hp;
	damage = dmg;
	
	source = new SDL_Rect();
	source->x = 0;
	source->y = 0;
	source->h = size;
	source->w = size;

	destination = new SDL_Rect();
	destination->h = size;
	destination->w = size;
	
	destination->x = x;
	destination->y = y;
	loadTexture(renderer, filePath);
	registerLuaFuncs();
}

Player::~Player() {
	
}

void Player::update(float deltaTime) {
	_inputs->update(this, deltaTime);
	script.getGlobal("update").push(deltaTime).call(1, 0);
}

int Player::lua_move(lua_State* lua) {
	Player* temp = (Player*)(lua_touserdata(lua, 3));
	temp->posX = lua_tonumber(lua, 1);
	temp->posY = lua_tonumber(lua, 2);
	temp->script.push(temp->posX);
	temp->script.push(temp->posY);
	temp->_inputs->setKeyPressed(PlayerInput::PlayerPressed::nothing);
	return 2;
}

int Player::lua_attack(lua_State* lua) {
	auto me = (Player*)lua_touserdata(lua, 1);
	auto x = (float)lua_tonumber(lua, 2);
	auto y = (float)lua_tonumber(lua, 3);
	auto range = (float)lua_tonumber(lua, 4);
	for (std::shared_ptr<Entity> entity : Engine::getInstance().getWorld()->getEntities()) {

	}

	return 0;
}

int Player::lua_getInputs(lua_State* lua) {
	Player* temp = (Player*)(lua_touserdata(lua, 1));
	lua_pushnumber(lua, temp->_inputs->getInput());
	return 1;
}

void Player::registerLuaFuncs() {
	lua_register(script.getState(), "getInputs", lua_getInputs);
	lua_register(script.getState(), "move", lua_move);
	lua_register(script.getState(), "attack", lua_attack);
}

void Player::loadTexture(SDL_Renderer* renderer, const std::string& filePath) {
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
