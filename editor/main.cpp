#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "lib/glad.h"

#include "lib/imgui.h"
#include "lib/imgui_impl_sdl_gl3.h"

#include <cstdio>
#include <string>

class Engine {
public:
	Engine() {
		_initSDL();
		_initGL();
		_initImGui();

		memset(_map, '.', 20 * 20 * sizeof(char));
	}

	virtual ~Engine() {
		IMG_Quit();
		ImGui_ImplSdlGL3_Shutdown();

		SDL_GL_DeleteContext(_context);
		SDL_DestroyWindow(_window);
		SDL_Quit();
	}

	void run() {
		bool openFile = false;
		bool saveFile = false;
		while (!_quit) {
			SDL_Event event;
			ImGuiIO& io = ImGui::GetIO();
			while (SDL_PollEvent(&event)) {
				ImGui_ImplSdlGL3_ProcessEvent(&event);
				switch (event.type) {
				case SDL_QUIT:
					_quit = true;
					break;
				case SDL_KEYDOWN:
					if (io.WantCaptureKeyboard)
						break;
					switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						_quit = true;
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
			}
			ImGui_ImplSdlGL3_NewFrame(_window);
			glClearColor(0, 0, 0, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_Always);
			ImGui::SetNextWindowSize(ImVec2(_width, _height), ImGuiSetCond_Once);
			ImGui::Begin("Editor", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);
			if (ImGui::BeginMenuBar()) {
				if (ImGui::BeginMenu("File")) {
					if (ImGui::MenuItem("New"))
						memset(_map, '.', 20 * 20 * sizeof(char));

					if (ImGui::MenuItem("Open"))
						openFile = true;

					if (ImGui::MenuItem("Save"))
						saveFile = true;

					ImGui::Separator();

					if (ImGui::MenuItem("Quit"))
						_quit = true;

					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

			static int current[20][20];
			for (int y = 0; y < 20; y++) {
				ImGui::PushID(y);
				for (int x = 0; x < 20; x++) {
					if (x)
						ImGui::SameLine();
					ImGui::PushID(x);
					if (ImGui::Button(std::string(&_map[y][x], 1).c_str(), ImVec2(32, 32)))
						ImGui::OpenPopup("Change tile");
					if (ImGui::BeginPopup("Change tile")) {
						static const char* tile[4] = {".", "#", "P", "E"};
						if (ImGui::Combo("Tile", &current[y][x], tile, sizeof(tile) / sizeof(tile[0])))
							_map[y][x] = tile[current[y][x]][0];

						ImGui::EndPopup();
					} else {
						char a = _map[y][x];
						current[y][x] = (a == '.') ? 0 : (a == '#') ? 1 : (a == 'P') ? 2 : (a == 'E') ? 3 : 0;
					}
					ImGui::PopID();
				}
				ImGui::PopID();
			}
			ImGui::End();

			if (openFile) {
				ImGui::OpenPopup("Open File");
				openFile = false;
			}

			if (saveFile) {
				ImGui::OpenPopup("Save File");
				saveFile = false;
			}
			static char file[255] = {0};

			if (ImGui::BeginPopupModal("Open File", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
				ImGui::InputText("Filename", file, sizeof(file));
				if (ImGui::Button("Open")) {
					FILE* fp = fopen(file, "rb");
					if (fp) {
						char line[21] = {0};
						for (int y = 0; y < 20; y++) {
							fscanf(fp, "%20s\n", line);
							memcpy(_map[y], line, 20);
						}
						fclose(fp);
					}
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::Button("Cancel"))
					ImGui::CloseCurrentPopup();

				ImGui::EndPopup();
			}

			if (ImGui::BeginPopupModal("Save File", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
				ImGui::InputText("Filename", file, sizeof(file));
				if (ImGui::Button("Save")) {
					FILE* fp = fopen(file, "wb");
					if (fp) {
						for (int y = 0; y < 20; y++) {
							fwrite(_map[y], 20, 1, fp);
							fputc('\n', fp);
							//fprintf(fp, "%20s\n", _map[y]);
						}
						fclose(fp);
					}
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::Button("Cancel"))
					ImGui::CloseCurrentPopup();

				ImGui::EndPopup();
			}

			ImGui::Render();

			SDL_GL_SwapWindow(_window);
		}
	}

private:
	constexpr static unsigned int _width = (unsigned int)(640 * 1.26);
	constexpr static unsigned int _height = (unsigned int)(640 * 1.20);
	bool _quit = false;
	SDL_Window* _window;
	SDL_GLContext _context;

	char _map[20][20];

	void _initSDL() {
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			fprintf(stderr, "SDL_Init: Failed to init!\n");
			fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
			throw "Failed to load SDL2";
		}

		if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
			fprintf(stderr, "IMG_Init: Failed to init, requires PNG support!\n");
			fprintf(stderr, "IMG_Init: %s\n", IMG_GetError());
			throw "Failed to load SDL2_image";
		}

		_window = SDL_CreateWindow("Trigon", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
		if (!_window)
			throw "Failed to create window";
	}
	void _initGL() {
		SDL_GL_LoadLibrary(NULL);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		_context = SDL_GL_CreateContext(_window);
		if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
			throw "Failed to init GLAD";

		glViewport(0, 0, _width, _height);
	}
	void _initImGui() { ImGui_ImplSdlGL3_Init(_window); }
};

int main(int argc, char** argv) {
	Engine engine;
	engine.run();
	return 0;
}
