#include "InputManager.h"

InputManager::InputManager()
{
	Inputs = std::make_unique<std::vector<eInput>>();
}

void InputManager::GetInput(GLFWwindow* window)
{
	if (Inputs->size() >= maxInputs) {
		Inputs->clear();
	}

	canChangeInput = framesSinceLastInput >= framesThreshold;

	if (canChangeInput)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			Inputs->push_back(eInput::Arrow_Up);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			Inputs->push_back(eInput::Arrow_Right);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			Inputs->push_back(eInput::Arrow_Left);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			Inputs->push_back(eInput::Arrow_Down);
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			Inputs->push_back(eInput::Arrow_Up);
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			Inputs->push_back(eInput::Arrow_Down);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			Inputs->push_back(eInput::Arrow_Left);
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			Inputs->push_back(eInput::Arrow_Right);
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			Inputs->push_back(eInput::Space_Bar);
		}
	}

	TimeHelper::CountFrames(!canChangeInput, framesSinceLastInput);	

	if (Inputs->size() != 0)
	{
		ReleasedKey(GLFW_KEY_SPACE, window);
		ReleasedKey(GLFW_KEY_RIGHT, window);
		ReleasedKey(GLFW_KEY_LEFT, window);
		ReleasedKey(GLFW_KEY_DOWN, window);
		ReleasedKey(GLFW_KEY_UP, window);
		ReleasedKey(GLFW_KEY_S, window);
		ReleasedKey(GLFW_KEY_A, window);
		ReleasedKey(GLFW_KEY_D, window);
		ReleasedKey(GLFW_KEY_W, window);
		currentInput = Inputs->back();
	}
}

void InputManager::ReleasedKey(int key, GLFWwindow* window)
{
	if (glfwGetKey(window, key) == GLFW_RELEASE && InputEnumToGlfwKey(Inputs->back()) == key)
	{
		canChangeInput = true;
		framesSinceLastInput = framesThreshold;
		Inputs->push_back(eInput::None);
	}
}

int InputManager::InputEnumToGlfwKey(eInput input)
{
	switch (input)
	{
	case eInput::Arrow_Up:
		return GLFW_KEY_W;
		break;
	case eInput::Arrow_Down:
		return GLFW_KEY_S;
		break;
	case eInput::Arrow_Left:
		return GLFW_KEY_A;
		break;
	case eInput::Arrow_Right:
		return GLFW_KEY_D;
		break;
	case eInput::Space_Bar:
		return GLFW_KEY_SPACE;
		break;
	}
	return 0;
}
