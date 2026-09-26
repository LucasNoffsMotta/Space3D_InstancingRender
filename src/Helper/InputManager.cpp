#include "InputManager.h"

InputManager::InputManager()
{
	Inputs[eInput::None] = true;
}

void InputManager::GetInput(GLFWwindow* window)
{
	canChangeInput = framesSinceLastInput >= framesThreshold;

	if (canChangeInput)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			Inputs[eInput::Arrow_Up] = true;
			Inputs[eInput::None] = false;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			Inputs[eInput::Arrow_Right] = true;
			Inputs[eInput::None] = false;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			Inputs[eInput::Arrow_Left] = true;
			Inputs[eInput::None] = false;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			Inputs[eInput::Arrow_Down] = true;
			Inputs[eInput::None] = false;
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			Inputs[eInput::Arrow_Up] = true;
			Inputs[eInput::None] = false;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			Inputs[eInput::Arrow_Down] = true;
			Inputs[eInput::None] = false;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			Inputs[eInput::Arrow_Left] = true;
			Inputs[eInput::None] = false;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			Inputs[eInput::Arrow_Right] = true;
			Inputs[eInput::None] = false;
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			Inputs[eInput::Space_Bar] = true;
			Inputs[eInput::None] = false;
		}
	}

	TimeHelper::CountFrames(!canChangeInput, framesSinceLastInput);	


	ReleasedKey(GLFW_KEY_SPACE, window);
	ReleasedKey(GLFW_KEY_RIGHT, window);
	ReleasedKey(GLFW_KEY_LEFT, window);
	ReleasedKey(GLFW_KEY_DOWN, window);
	ReleasedKey(GLFW_KEY_UP, window);
	ReleasedKey(GLFW_KEY_S, window);
	ReleasedKey(GLFW_KEY_A, window);
	ReleasedKey(GLFW_KEY_D, window);
	ReleasedKey(GLFW_KEY_W, window);

}

void InputManager::ReleasedKey(int key, GLFWwindow* window)
{
	if (glfwGetKey(window, key) == GLFW_RELEASE && Inputs[InputGlfwKeyToEnum(key)] == true)
	{
		canChangeInput = true;
		framesSinceLastInput = framesThreshold;
		Inputs[eInput::None] = true;
		Inputs[InputGlfwKeyToEnum(key)] = false;
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

eInput InputManager::InputGlfwKeyToEnum(int key)
{
	switch (key)
	{
	case GLFW_KEY_W:
		return eInput::Arrow_Up;
		break;
	case GLFW_KEY_S:
		return eInput::Arrow_Down;
		break;
	case GLFW_KEY_A:
		return eInput::Arrow_Left;
		break;
	case GLFW_KEY_D:
		return eInput::Arrow_Right;
		break;
	case GLFW_KEY_SPACE:
		return eInput::Space_Bar;
		break;
	}
	return eInput::None;
}
