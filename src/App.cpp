#include "App.h"
#include <glad/glad.h>
#include <SDL_opengl.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Cube.h"

/*
* TODO: Abstract VAO/EBO/VBO stuff into a class
*/

App::App(unsigned int width_, unsigned int height_) :
	OpenGLApp(width_, height_)
{
}

App::~App()
{
	shutdown();
}

void App::setup()
{
	SDL_SetWindowGrab(window, SDL_TRUE);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);

	program = std::make_unique<Shader>("glsl/basic.vert", "glsl/basic.frag");
	texture = std::make_shared<Texture2D>("textures/container2.png");
	objects.emplace_back(new Cube(this, texture, glm::vec3(-1.0f, 0.0f, 0.0f)));
	camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
}

void App::processInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT)
		{
			isRunning = false;
		}

		const Uint8* keyState = SDL_GetKeyboardState(nullptr);
		if (keyState[SDL_SCANCODE_ESCAPE])
		{
			isRunning = false;
		}

		camera->processInput(&e);
	}
}

void App::logic(float deltaTime)
{
	camera->update(deltaTime);
}

void App::render()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto obj : objects)
	{
		obj->render(program);
	}

	SDL_GL_SwapWindow(window);
}

void App::shutdown()
{

}
