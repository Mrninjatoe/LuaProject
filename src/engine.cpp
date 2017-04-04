#include "engine.hpp"
#include <SDL2\SDL_image.h>

// Each room has a orthographic view with the size of -10 to 10 in x and y direction
// Each Environment block represents a single digit in this space.
// Player and NPC to be decided...

Engine::Engine(){
	_init();
	_run();
}

void Engine::_run() {
	while (!_quit) {
		SDL_GL_SwapWindow(_gMainWindow);
		while (SDL_PollEvent(&_event)) {
			if (_event.type == SDL_QUIT)
				_quit = true;
		}

		// Clear screen.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Update and Render.
		_characterManager->_updateEntities();
		_normalShader->bindShader();
		_characterManager->_renderEntities(_normalShader);
	}
}

void Engine::_init() {
	_initVariables();
	_initSDL();
	_initGL();
	_initViewPort();
	_initWorld();
	_initShaders();
}

void Engine::_initVariables() {
	_vsync = true;
	_quit = false;

	_width = 512;
	_height = 512;

	glm::vec3 eye(0, 0, -1);
	glm::vec3 center(eye + glm::vec3(0));
	glm::vec3 up(0, -1, 0);
	_view = glm::lookAt(eye, glm::vec3(0), up);
	_projection = glm::ortho(-15.0f, 15.0f, -15.0f, 15.0f, 0.1f, 1.0f);
}

void Engine::_initWorld() {
	_characterManager = std::make_shared<EntityManager>();
}

void Engine::_initShaders() {
	_normalShader = std::make_shared<ShaderProgram>("assets/shaders/vertex.vert",
		"assets/shaders/fragment.frag");
	_normalShader->bindShader().addUniform("vp", _projection * _view);
}

void Engine::_initSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		throw "Failed to intialize SDL, SDL_Error: %s\n", SDL_GetError();
	else {
		_gMainWindow = SDL_CreateWindow(
			"LuaProject",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			_width,
			_height,
			SDL_WINDOW_OPENGL
		);

		if (_gMainWindow == NULL)
			throw "Failed to initalize SDL Window, SDL_ERROR: %s\n", SDL_GetError();

		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
			throw "Failed to load SDL_Image.\n";

		// SDL Screen Options
		if(_vsync == true)
			SDL_GL_SetSwapInterval(1);
	}
}	

void Engine::_initGL() {
	// Debugging context
	SDL_GL_SetAttribute(
		SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG
	);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);

	_gContext = SDL_GL_CreateContext(_gMainWindow);
	if (_gContext == NULL)
		throw "Failed to create context!";
	else {
		// Check OpenGL properties
		printf("OpenGL loaded\n");
		gladLoadGLLoader(SDL_GL_GetProcAddress);
		printf("Vendor:   %s\n", glGetString(GL_VENDOR));
		printf("Renderer: %s\n", glGetString(GL_RENDERER));
		printf("Version:  %s\n", glGetString(GL_VERSION));

		// Disabling back face culling and depth testing because it's going to be a 2D game.
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);

		// Debugging stuff
		glEnable(GL_DEBUG_OUTPUT);
		// Synchronous needed to get the callback from the same thread as the openGL API.
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		// Check engine.hpp for the openglCallbackFunction.
		glDebugMessageCallback(openglCallbackFunction, nullptr);
		glDebugMessageControl(
			GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true
		);
	}
}

void Engine::_initViewPort() {
	glViewport(0, 0, _width, _height);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}
