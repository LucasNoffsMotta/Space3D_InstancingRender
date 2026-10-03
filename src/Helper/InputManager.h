#pragma once
#include <memory>
#include <vector>
#include "eInput.h"
#include "TimeHelper.h"
#include <GLFW/glfw3.h>
#include <map>
#include <glm/glm.hpp>


class InputManager
{
private:
	int framesThreshold = 4000;
	int framesSinceLastInput = 30;
	int maxInputs = 10;
	bool canChangeInput = true;


public:
	 InputManager();
	 double mouseX;
	 double mouseY;
	 std::map<eInput, bool> Inputs;
	 eInput currentInput = eInput::None;
	 void GetInput(GLFWwindow* window);
	 void ReleasedKey(int key, GLFWwindow* window);
	 int InputEnumToGlfwKey(eInput input);
	 eInput InputGlfwKeyToEnum(int key);
	 void GetMouseScreenPos(GLFWwindow* window);
	 glm::vec3 GetMouseRayCastDirection(glm::mat4& projectionMatrix, glm::mat4& viewMatrix, int screen_Height, int screen_Width, double mouseX, double mouseY);
};