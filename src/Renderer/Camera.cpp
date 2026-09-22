#include "Camera.h"
#include "../Helper/TimeHelper.h"


void Camera::SetSpotLight()
{
}

Camera::Camera(glm::vec3& camPos, glm::vec3& camFront, glm::vec3& camUp)
{
	CameraPos = camPos;
	CameraFront = camFront;
	CameraUp = camUp;
	SetSpotLight();
}

void Camera::SetPos(glm::vec3& pos)
{
	CameraPos = pos;
}

void Camera::SetFront(glm::vec3& front)
{
	CameraFront = front;
}

void Camera::SetUp(glm::vec3& up)
{
	CameraUp = up;
}


void Camera::CalculateDirection(float xoffset, float yoffset)
{
	Yaw += xoffset * TimeHelper::dt;
	Pitch += yoffset * TimeHelper::dt;

	std::cout << Yaw << std::endl;

	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	direction.y = sin(glm::radians(Pitch));
	direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	CameraFront = glm::normalize(direction);
	std::cout << "Dir X: " << direction.x << "/ Dir Y: " << direction.y << "/ Dir Z: " << direction.z << std::endl;
}

void Camera::SetMoveSpeed(float newSpeed)
{
	MoveSpeed = newSpeed;
}

void Camera::HandleKeybordInput(InputManager* controller)
{
	if (controller->currentInput == eInput::Arrow_Up)
	{
		if (mode == eCameraMode::Free) CameraPos += (MoveSpeed * CameraFront) * TimeHelper::GetDeltaTime();
		else if (mode == eCameraMode::TopDown) CameraPos.z -= (MoveSpeed * TimeHelper::GetDeltaTime());
	}

	if (controller->currentInput == eInput::Arrow_Down)
	{
		if (mode == eCameraMode::Free) CameraPos -= (MoveSpeed * CameraFront) * TimeHelper::GetDeltaTime();
		else if (mode == eCameraMode::TopDown) CameraPos.z += (MoveSpeed * TimeHelper::GetDeltaTime());
	}

	if (controller->currentInput == eInput::Arrow_Left)
	{
		CameraPos -= (glm::normalize(glm::cross(CameraFront, CameraUp)) * MoveSpeed) * TimeHelper::GetDeltaTime();
	}

	if (controller->currentInput == eInput::Arrow_Right)
	{

		CameraPos += (glm::normalize(glm::cross(CameraFront, CameraUp)) * MoveSpeed) * TimeHelper::GetDeltaTime();
	}

	if (controller->currentInput == eInput::Space_Bar)
	{
		if (mode == eCameraMode::Free) {
			CameraPos = topDownPosition;
			CameraFront = topDownDirection;
			mode = eCameraMode::TopDown;
		}

		else
		{
			mode = eCameraMode::Free;
		}
	}
}

glm::mat4 Camera::CalculateView()
{
	return glm::lookAt(CameraPos, CameraPos + CameraFront, CameraUp);
}

glm::mat4 Camera::Update(Window& window, InputManager* controller)
{
	double mouseX = 1;
	double mouseY = 1;
	glfwGetCursorPos(window.window, &mouseX, &mouseY);

	if (mode == eCameraMode::Free)
	{
		HandleMouseInput(mouseX, mouseY);
	}
	HandleKeybordInput(controller);
	std::cout << "Cam x: " << CameraPos.x << " // Cam y:" << CameraPos.y << " // Cam Z:" << CameraPos.z << std::endl;
	return CalculateView();
}

void Camera::HandleMouseInput(double xpos, double ypos)
{
	if (FirstMouseMovement)
	{
		LastX = xpos;
		LastY = ypos;
		FirstMouseMovement = false;
	}

	float xoffset = xpos - LastX;
	float yoffset = ypos - LastY;
	LastX = xpos;
	LastY = ypos;

	const float sensivity = 70.f;

	xoffset *= sensivity;
	yoffset *= sensivity *-1.0f;

	CalculateDirection(xoffset, yoffset);
}
