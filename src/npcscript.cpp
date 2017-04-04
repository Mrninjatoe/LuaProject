#include "npcscript.hpp"

NPCScript::NPCScript(const std::string &scriptName){
	if (luaL_dofile(_lState, scriptName.c_str()))
		printf("Failed to load script: %s\n", scriptName.c_str());

}

int NPCScript::l_addNPC() {

	return 0;
}