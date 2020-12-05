#pragma once
#include "BasicObject.h"
#include <vector>

class Cube : public BasicObject
{
public:
	Cube(OpenGLApp* owner, std::shared_ptr<Texture2D> texture_, const glm::vec3& position_ = glm::vec3(0.0f, 0.0f, 0.0f),
		const glm::vec3& scale_ = glm::vec3(1.0f, 1.0f, 1.0f),
		float rotX_ = 0.0f, float rotY_ = 0.0f, float rotZ_ = 0.0f);

	void render(std::shared_ptr<Shader> shader) override;

private:
	static const std::vector<float> vertices;
};