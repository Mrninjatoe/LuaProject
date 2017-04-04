#include "script.hpp"
#include <fstream>

Script::Script() {
	// Creates a lua_State object ready to make lua calls.
	_lState = luaL_newstate();
	luaL_openlibs(_lState);
}

//std::string scriptSource = "";
//std::ifstream scriptFile(scriptName.c_str());
//if (scriptFile.is_open()) {
//	std::string line = "";
//	while (getline(scriptFile, line)) {
//		scriptSource += line + "\n";
//	}
//	scriptFile.close();
//}
//else
//	printf("Could not open lua script, check path.\n");
//
//int status = luaL_loadstring(_lState, scriptSource.c_str());
//if (status)
//	printf("Error reading lua script: %s\n", lua_tostring(_lState, -1));