#include "InputManager.h"

InputManager::InputManager()
{
	Inputs[eInput::None] = true;
	InputList.push_back(eInput::Arrow_Up);
	InputList.push_back(eInput::RenderMode_Debug);
	InputList.push_back(eInput::RenderMode_DepthTest);
	InputList.push_back(eInput::RenderMode_LightsOff);
	InputList.push_back(eInput::RenderMode_LitAndReflection);
}

void InputManager::GetInput()
{

	if (glfwGetKey(windowReference, GLFW_KEY_W) == GLFW_PRESS)
	{
		Inputs[eInput::Arrow_Up] = true;
		Inputs[eInput::None] = false;
	}
	if (glfwGetKey(windowReference, GLFW_KEY_D) == GLFW_PRESS)
	{
		Inputs[eInput::Arrow_Right] = true;
		Inputs[eInput::None] = false;
	}
	if (glfwGetKey(windowReference, GLFW_KEY_A) == GLFW_PRESS)
	{
		Inputs[eInput::Arrow_Left] = true;
		Inputs[eInput::None] = false;
	}
	if (glfwGetKey(windowReference, GLFW_KEY_S) == GLFW_PRESS)
	{
		Inputs[eInput::Arrow_Down] = true;
		Inputs[eInput::None] = false;
	}
	if (glfwGetKey(windowReference, GLFW_KEY_UP) == GLFW_PRESS)
	{
		Inputs[eInput::Arrow_Up] = true;
		Inputs[eInput::None] = false;
	}
	if (glfwGetKey(windowReference, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		Inputs[eInput::Arrow_Down] = true;
		Inputs[eInput::None] = false;
	}
	if (glfwGetKey(windowReference, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		Inputs[eInput::Arrow_Left] = true;
		Inputs[eInput::None] = false;
	}
	if (glfwGetKey(windowReference, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		Inputs[eInput::Arrow_Right] = true;
		Inputs[eInput::None] = false;
	}
	if (glfwGetKey(windowReference, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Inputs[eInput::Space_Bar] = true;
		Inputs[eInput::None] = false;
	}

	if (glfwGetKey(windowReference, GLFW_KEY_P) == GLFW_PRESS)
	{
		Inputs[eInput::RotatePitch] = true;
		Inputs[eInput::None] = false;
	}

	if (glfwGetKey(windowReference, GLFW_KEY_Y) == GLFW_PRESS)
	{
		Inputs[eInput::RotateYaw] = true;
		Inputs[eInput::None] = false;
	}

	if (glfwGetKey(windowReference, GLFW_KEY_R) == GLFW_PRESS)
	{
		Inputs[eInput::RotateRoll] = true;
		Inputs[eInput::None] = false;
	}

	if (glfwGetKey(windowReference, GLFW_KEY_1) == GLFW_PRESS)
	{
		Inputs[eInput::RenderMode_LightsOff] = true;
		Inputs[eInput::None] = false;
	}

	if (glfwGetKey(windowReference, GLFW_KEY_2) == GLFW_PRESS)
	{
		Inputs[eInput::RenderMode_LitAndReflection] = true;
		Inputs[eInput::None] = false;
	}

	if (glfwGetKey(windowReference, GLFW_KEY_3) == GLFW_PRESS)
	{
		Inputs[eInput::RenderMode_Debug] = true;
		Inputs[eInput::None] = false;
	}

	if (glfwGetKey(windowReference, GLFW_KEY_4) == GLFW_PRESS)
	{
		Inputs[eInput::RenderMode_DepthTest] = true;
		Inputs[eInput::None] = false;
	}

	ReleasedKey(GLFW_KEY_SPACE);
	ReleasedKey(GLFW_KEY_RIGHT);
	ReleasedKey(GLFW_KEY_LEFT);
	ReleasedKey(GLFW_KEY_DOWN);
	ReleasedKey(GLFW_KEY_UP);
	ReleasedKey(GLFW_KEY_S);
	ReleasedKey(GLFW_KEY_A);
	ReleasedKey(GLFW_KEY_D);
	ReleasedKey(GLFW_KEY_W);
	ReleasedKey(GLFW_KEY_P);
	ReleasedKey(GLFW_KEY_Y);
	ReleasedKey(GLFW_KEY_R);

	ReleasedKey(GLFW_KEY_1);
	ReleasedKey(GLFW_KEY_2);
	ReleasedKey(GLFW_KEY_3);
	ReleasedKey(GLFW_KEY_4);
}

void InputManager::ReleasedKey(int key)
{
	if (glfwGetKey(windowReference, key) == GLFW_RELEASE && Inputs[InputGlfwKeyToEnum(key)] == true)
	{
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
	case GLFW_KEY_P:
		return eInput::RotatePitch;
		break;
	case GLFW_KEY_Y:
		return eInput::RotateYaw;
		break;
	case GLFW_KEY_R:
		return eInput::RotateRoll;
	case GLFW_KEY_1:
		return eInput::RenderMode_LightsOff;
		break;
	case GLFW_KEY_2:
		return eInput::RenderMode_LitAndReflection;
		break;
	case GLFW_KEY_3:
		return eInput::RenderMode_Debug;
		break;
	case GLFW_KEY_4:
		return eInput::RenderMode_DepthTest;
		break;
	}
	
	return eInput::None;
}

//TEST
void InputManager::GetMouseScreenPos()
{
	glfwGetCursorPos(windowReference, &mouseX, &mouseY);
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
