#pragma once
#include <glm/glm.hpp>
#include "Shader.h"
#include <memory>
#include "Texture2D.h"

class OpenGLApp;

class BasicObject
{
public:
	BasicObject(OpenGLApp* owner, std::shared_ptr<Texture2D> texture_, const glm::vec3& position_ = glm::vec3(0.0f, 0.0f, 0.0f),
		const glm::vec3& scale_ = glm::vec3(1.0f, 1.0f, 1.0f),
		float rotX_ = 0.0f, float rotY_ = 0.0f, float rotZ_ = 0.0f);

	virtual void render(std::shared_ptr<Shader> shader) = 0;

protected:
	OpenGLApp* owner;

	unsigned int vao;
	glm::vec3 position;
	glm::vec3 scale;

	// Rotation about x,y,z axes (in degrees)
	float rotX;
	float rotY;
	float rotZ;

	std::shared_ptr<Texture2D> texture;
};

