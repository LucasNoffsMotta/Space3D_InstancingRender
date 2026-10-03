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

//TEST
void InputManager::GetMouseScreenPos(GLFWwindow* window)
{
	glfwGetCursorPos(window, &mouseX, &mouseY);
}

glm::vec3 InputManager::GetMouseRayCastDirection(glm::mat4& projectionMatrix, glm::mat4& viewMatrix, int screen_Height, int screen_Width, double mouseX, double mouseY)
{
	float x = (2.0 * mouseX) / screen_Width - 1.0f;
	float y = 1.0f - (2.0f * mouseY) / screen_Height;
	float z = -1.0f;
	glm::vec4 ray_clip = glm::vec4(x, y, z, 1.0f);
	glm::vec4 ray_eye = glm::inverse(projectionMatrix) * ray_clip;
	ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
	glm::vec3 ray_wor = (glm::inverse(viewMatrix) * ray_eye);
	return glm::normalize(ray_wor);
}
