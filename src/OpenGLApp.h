#pragma once
#include <glad/glad.h>
#include <SDL.h>
#include <SDL_opengl.h>

class OpenGLApp
{
public:
	OpenGLApp(unsigned int width_, unsigned int height_);
	virtual ~OpenGLApp();

	void run();

protected:
	virtual void setup() = 0;
	virtual void processInput() = 0;
	virtual void logic(float deltaTime) = 0;
	virtual void render() = 0;
	virtual void shutdown() = 0;

	SDL_Window* window;
	unsigned int width;
	unsigned int height;
	bool isRunning;

private:
	SDL_GLContext glContext;
};

