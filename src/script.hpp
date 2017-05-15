#pragma once
#include <Lua/lua.hpp>
#include <Lua/lauxlib.h>
#include <Lua/lualib.h>
#include <string>

class Script {
public:
	Script();
	virtual ~Script();
	Script& doFile(const std::string& fileName);
	Script& openLibs();
	Script& getGlobal(const std::string& name);
	Script& setGlobal(const std::string& name);
	Script& pop();
	Script& pop(float& n);
	Script& pop(bool& condition);
	Script& push(float n);
	Script& push(bool condition);
private:
	lua_State* _state;
};