#pragma once
#include "entity.hpp"
class Environment : public Entity{
public:
	Environment();
	virtual ~Environment() {};
	virtual void update() = 0;
private:

};