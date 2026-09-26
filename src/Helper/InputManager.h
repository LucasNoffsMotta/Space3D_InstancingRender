#pragma once
#include <memory>
#include <vector>
#include "eInput.h"
#include "TimeHelper.h"
#include <GLFW/glfw3.h>
#include <map>


class InputManager
{
private:
	int framesThreshold = 30;
	int framesSinceLastInput = 30;
	int maxInputs = 10;
	bool canChangeInput = true;

public:
	 InputManager();
	 std::map<eInput, bool> Inputs;
	 eInput currentInput = eInput::None;
	 void GetInput(GLFWwindow* window);
	 void ReleasedKey(int key, GLFWwindow* window);
	 int InputEnumToGlfwKey(eInput input);
	 eInput InputGlfwKeyToEnum(int key);
};