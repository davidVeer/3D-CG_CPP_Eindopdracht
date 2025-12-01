#pragma once
#include <glm/glm.hpp>

struct GLFWwindow;

__interface ICameraStrategy {
	glm::mat4 getMatrix();
	void update(GLFWwindow* window);
};