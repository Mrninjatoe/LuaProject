#pragma once
#include <Lua/lua.hpp>
#include <Lua/lua.h>

class Script {
public:
	Script();
	virtual ~Script();
private:
	lua_State* _state;
};