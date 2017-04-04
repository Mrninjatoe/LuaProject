#pragma once
#include "script.hpp"
class NPCScript : public Script {
public:
	NPCScript(const std::string &scriptName);
	virtual ~NPCScript() {};
	int l_addNPC();
private:

};