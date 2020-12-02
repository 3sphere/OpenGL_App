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
	forwardSpeed(0.0f),
	rightSpeed(0.0f),
	mouseSensitivity(sens),
	firstMouse(true)
{
	updateCameraVectors();
}

void Camera::processInput(const uint8_t* keyboardState, int mouseX, int mouseY)
{
	// keyboard input
	forwardSpeed = rightSpeed = 0.0f;
	if (keyboardState[SDL_SCANCODE_W])
	{
		forwardSpeed += movementSpeed;
	}
	if (keyboardState[SDL_SCANCODE_S])
	{
		forwardSpeed -= movementSpeed;
	}
	if (keyboardState[SDL_SCANCODE_A])
	{
		rightSpeed -= movementSpeed;
	}
	if (keyboardState[SDL_SCANCODE_D])
	{
		rightSpeed += forwardSpeed;
	}

	// mouse input
	

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	else if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::update(float deltaTime)
{
	//position += front * dir.y * movementSpeed * deltaTime;
	//position += right * dir.x * movementSpeed * deltaTime;
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
	up = glm::normalize(glm::cross(right, front));
}
