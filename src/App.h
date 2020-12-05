#pragma once
#include "OpenGLApp.h"
#include <memory>
#include "Shader.h"
#include "Texture2D.h"
#include "BasicObject.h"
#include <vector>

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

	std::shared_ptr<Shader> program;
	std::shared_ptr<Texture2D> texture;
	std::vector<std::shared_ptr<BasicObject>> objects;
};

