#pragma once
#include "OpenGLApp.h"
#include <memory>
#include "Shader.h"
#include "Texture2D.h"
#include "Camera.h"

class App : public OpenGLApp
{
public:
	App(unsigned int width, unsigned int height);
	~App();

private:
	void setup() override;
	void processInput() override;
	void logic(float deltaTime) override;
	void render() override;
	void shutdown() override;

	std::unique_ptr<Shader> program;
	std::unique_ptr<Texture2D> texture;
	std::unique_ptr<Camera> camera;
	unsigned int vao;
};

