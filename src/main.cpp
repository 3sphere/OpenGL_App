#include <glad/glad.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include "Shader.h"
#include <memory>
#include "App.h"

int main(int argc, char** argv)
{
	App app(800, 600);
	app.run();

	return 0;
}