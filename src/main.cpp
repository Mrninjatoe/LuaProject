#include <stdio.h>
#include "engine.hpp"
#include <stdlib.h>
#include <SDL2/SDL.h>

#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define MEMORY_DEBUG() _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#else
#define MEMORY_DEBUG()
#endif

int main(int argc, char** argv) {
	MEMORY_DEBUG();
	return Engine::getInstance().run();
}
