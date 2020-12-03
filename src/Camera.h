#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL.h>

class Camera
{
public:
	Camera(const glm::vec3& pos, float yaw = -90.0f, float pitch = 0.0f, float speed = MOVEMENT_SPEED, float sens = MOUSE_SENSITIVITY);
	
	glm::mat4 getViewMatrix() const { return glm::lookAt(position, position+front, glm::vec3(0.0f, 1.0f, 0.0f)); }
	void setMouseSensitivity(float sens) { mouseSensitivity = sens; }
	void setMovementSpeed(float speed) { movementSpeed = speed; }

	void processInput(SDL_Event* e);
	void update(float deltaTime);

private:
	void updateCameraVectors();

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	float yaw;
	float pitch;
	float movementSpeed;
	int dirForward;
	int dirRight;
	float mouseSensitivity;

	static const float MOVEMENT_SPEED;
	static const float MOUSE_SENSITIVITY;
};