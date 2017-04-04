#pragma once
#include <SDL2\SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <glad/glad.h>
#include <vector>
#include "entity.hpp"
#include "player.hpp"
#include "shaderprogram.hpp"
#include "script.hpp"
#include "entitymanager.hpp"
#include "leveleditor.hpp"

class Engine {
public:
	Engine();
	virtual ~Engine() {};
	void _init();
	void _initVariables();
	void _initSDL();
	void _initGL();
	void _initViewPort();
	void _initWorld();
	void _initShaders();
	void _run();
	
	// For openGL Debugging
	static void APIENTRY openglCallbackFunction(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam){
			(void)source; (void)type; (void)id;
			(void)severity; (void)length; (void)userParam;
			fprintf(stderr, "%s\n", message);
			if (severity == GL_DEBUG_SEVERITY_HIGH) 
			{
				fprintf(stderr, "Will probably break the program, aborting!\n");
				abort();
			}
	}

private:
	int _width;
	int _height;
	int _fps;

	bool _quit;
	bool _vsync;
	bool _editorMode;

	SDL_Event _event;
	SDL_GLContext _gContext;
	SDL_Window* _gMainWindow;

	std::shared_ptr<ShaderProgram>	_normalShader;
	std::shared_ptr<EntityManager>	_characterManager;
	std::shared_ptr<LevelEditor>	_levelEditor;

	std::vector<std::shared_ptr<Room>> _rooms;
	glm::mat4 _view;
	glm::mat4 _projection;
};