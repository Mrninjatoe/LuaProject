#pragma once
#include <Lua\lua.hpp>
#include <Lua\lualib.h>
#include <string>
class Script {
public:
	Script();
	virtual ~Script() {};
protected:
	lua_State* _lState;
private:

};