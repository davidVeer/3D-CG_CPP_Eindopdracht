#pragma once
#include "CameraStrategy.h"

class KeyboardAndMouseCamera : public ICameraStrategy {
	
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec2 rotation = glm::vec2(0, 0);
	
	void processKeyboardInputs(GLFWwindow* window);
	void processMouseInputs(GLFWwindow* window);
	void move(float angle, float fac);
public:

	KeyboardAndMouseCamera(GLFWwindow* window);
	~KeyboardAndMouseCamera() = default;
	glm::mat4 getMatrix();
	void update(GLFWwindow* window);
};