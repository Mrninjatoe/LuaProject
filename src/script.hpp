#pragma once
#include <Lua/lua.hpp>
#include <Lua/lauxlib.h>
#include <Lua/lualib.h>
#include <string>
#include <vector>

class Script {
public:
	Script();
	virtual ~Script();
	Script& doFile(const std::string& fileName);
	Script& openLibs();
	Script& getGlobal(const std::string& name);
	Script& setGlobal(const std::string& name);
	Script& setField(const std::string& name, int index);
	Script& pop();
	Script& pop(float& n);
	Script& pop(int& n);
	Script& pop(bool& condition);
	Script& push(float n);
	Script& push(int n);
	Script& push(bool condition);
	Script& push(void* userdata);
	Script& call(int nrOfArgs, int nrOfReturns);
	Script& clearStack();
	lua_State* getState() { return _state; }
private:
	lua_State* _state;

	static int _lua_errorHandler(lua_State* lua);
};
