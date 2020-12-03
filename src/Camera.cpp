#include "Camera.h"
#include <SDL.h>
#include <iostream>

const float Camera::MOVEMENT_SPEED = 2.5f;
const float Camera::MOUSE_SENSITIVITY = 0.1f;

Camera::Camera(const glm::vec3& pos, float yaw_, float pitch_, float speed, float sens) :
	position(pos),
	front(0.0f, 0.0f, -1.0f),
	yaw(yaw_),
	pitch(pitch_),
	movementSpeed(speed),
	dirForward(0),
	dirRight(0),
	mouseSensitivity(sens)
{
	updateCameraVectors();
}

void Camera::processInput(SDL_Event* e)
{
	// Keyboard input
	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
	dirForward = dirRight = 0;
	if (keyboardState[SDL_SCANCODE_W])
	{
		dirForward += 1;
	}
	if (keyboardState[SDL_SCANCODE_S])
	{
		dirForward -= 1;
	}
	if (keyboardState[SDL_SCANCODE_A])
	{
		dirRight -= 1;
	}
	if (keyboardState[SDL_SCANCODE_D])
	{
		dirRight += 1;
	}

	// Mouse input
	if (e->type == SDL_MOUSEMOTION)
	{
		yaw += e->motion.xrel * mouseSensitivity;
		pitch -= e->motion.yrel * mouseSensitivity;

		if (pitch > 89.0f)
		{
			pitch = 89.0f;
		}
		else if (pitch < -89.0f)
		{
			pitch = -89.0f;
		}
	}

	updateCameraVectors();
}

void Camera::update(float deltaTime)
{
	if (dirRight != 0.0f || dirForward != 0.0f)
	{
		glm::vec3 direction = glm::normalize(front * (float)dirForward + right * (float)dirRight);
		position += direction * movementSpeed * deltaTime;
	}
}

void Camera::updateCameraVectors()
{
	glm::vec3 newFront;
	newFront.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	front = glm::normalize(newFront);
	right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
	up = glm::normalize(glm::cross(right, front));
}
