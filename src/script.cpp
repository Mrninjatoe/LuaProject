#include "script.hpp"

Script::Script() {
	_state = luaL_newstate();
}

Script::~Script() {
	lua_close(_state);
}

Script& Script::doFile(const std::string& fileName) {
	luaL_dofile(_state, fileName.c_str());
	return *this;
}

Script& Script::openLibs() {
	luaL_openlibs(_state);
	return *this;
}

Script& Script::getGlobal(const std::string& name) {
	lua_getglobal(_state, name.c_str());
	return *this;
}

Script& Script::setGlobal(const std::string& name) {
	lua_setglobal(_state, name.c_str());
	return *this;
}

Script& Script::setField(const std::string& name, int index) {
	lua_setfield(_state, index, name.c_str());
	return *this;
}

Script& Script::pop() {
	lua_pop(_state, 1);
	return *this;
}

Script& Script::pop(float& n) {
	n = (float)lua_tonumber(_state, -1);
	lua_pop(_state, 1);
	return *this;
}

Script& Script::pop(int& n) {
	n = lua_tointeger(_state, -1);
	lua_pop(_state, 1);
	return *this;
}

Script& Script::pop(bool& condition) {
	condition = (bool)lua_toboolean(_state, -1);
	lua_pop(_state, 1);
	return *this;
}

Script& Script::push(float n) {
	lua_pushnumber(_state, n);
	return *this;
}

Script& Script::push(int n) {
	lua_pushnumber(_state, n);
	return *this;
}

Script& Script::push(bool condition) {
	lua_pushboolean(_state, condition);
	return *this;
}

Script& Script::push(void* userdata) {
	lua_pushlightuserdata(_state, userdata);
	return *this;
}

Script& Script::call(int nrOfArgs, int nrOfReturns) {
	lua_call(_state, nrOfArgs, nrOfReturns);
	return *this;
}

Script& Script::clearStack() {
	int n = lua_gettop(_state);
	lua_pop(_state, n);
	return *this;
}