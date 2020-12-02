#include "OpenGLApp.h"
#include <string>
#include <iostream>
#include "stb_image.h"

OpenGLApp::OpenGLApp(unsigned int width_, unsigned int height_) :
	window(nullptr),
	width(width_),
	height(height_),
	isRunning(false),
	glContext(nullptr)
{
	// Initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "Failed to initialise SDL\n";
		throw(SDL_GetError());
	}

	// Use OpenGL 3.3 Core Profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Create window and OpenGL context
	window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | !SDL_WINDOW_RESIZABLE);
	if (!window)
	{
		std::cout << "Failed to create window\n";
		throw(SDL_GetError());
	}
	glContext = SDL_GL_CreateContext(window);

	// Load OpenGL function pointers with GLAD
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		throw("Failed to initialise GLAD\n");
	}

	stbi_set_flip_vertically_on_load(true);
}

OpenGLApp::~OpenGLApp()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void OpenGLApp::run()
{
	isRunning = true;
	setup();

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	while (isRunning)
	{
		// Per-frame time logic
		float currentFrame = SDL_GetTicks() / 1000.0f;
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput();
		logic(deltaTime);
		render();
	}

	shutdown();
}
