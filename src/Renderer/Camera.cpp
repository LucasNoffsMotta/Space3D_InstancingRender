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


void Camera::CalculateDirection(float xoffset, float yoffset, bool constraintOnPitch)
{
	Yaw += xoffset * TimeHelper::dt;
	Pitch += yoffset * TimeHelper::dt;

	std::cout << "Pitch looking down:  " << Pitch << std::endl;

	//std::cout << Yaw << std::endl;

	if (constraintOnPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}
	glm::vec3 direction;
	direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	direction.y = sin(glm::radians(Pitch));
	direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	CameraFront = glm::normalize(direction);
	//std::cout << "Dir X: " << direction.x << "/ Dir Y: " << direction.y << "/ Dir Z: " << direction.z << std::endl;
}

//Calculates the Yaw impact on the camera direction, used to make the minimap rotate using a top down view!
void Camera::CalculateDirectionYawOnly(float newYaw)
{
	CameraFront.z = sin(glm::radians(newYaw)) * cos(glm::radians(-89.f));
	CameraFront.x = cos(glm::radians(newYaw)) * cos(glm::radians(-89.f));
	CameraFront = glm::normalize(CameraFront);
}

void Camera::SetMoveSpeed(float newSpeed)
{
	MoveSpeed = newSpeed;
}

void Camera::HandleKeybordInput(InputManager* controller)
{
	if (controller->Inputs[eInput::None] == true || mode == eCameraMode::TopDown)
	{
		return;
	}

	if (controller->Inputs[eInput::Arrow_Up])
	{
		if (mode == eCameraMode::Free) CameraPos += (MoveSpeed * CameraFront) * TimeHelper::GetDeltaTime();
		else if (mode == eCameraMode::TopDown) CameraPos.z -= (MoveSpeed * TimeHelper::GetDeltaTime());
	}

	if (controller->Inputs[eInput::Arrow_Down])
	{
		if (mode == eCameraMode::Free) CameraPos -= (MoveSpeed * CameraFront) * TimeHelper::GetDeltaTime();
		else if (mode == eCameraMode::TopDown) CameraPos.z += (MoveSpeed * TimeHelper::GetDeltaTime());
	}

	if (controller->Inputs[eInput::Arrow_Left])
	{
		CameraPos -= (glm::normalize(glm::cross(CameraFront, CameraUp)) * MoveSpeed) * TimeHelper::GetDeltaTime();
	}

	if (controller->Inputs[eInput::Arrow_Right])
	{

		CameraPos += (glm::normalize(glm::cross(CameraFront, CameraUp)) * MoveSpeed) * TimeHelper::GetDeltaTime();
	}
}

void Camera::Turn(float degrees)
{
	Yaw += degrees;
	HandleMouseInput(0, 0, false);
}


glm::mat4 Camera::CalculateView()
{
	return glm::lookAt(CameraPos, CameraPos + CameraFront, CameraUp);
}

glm::mat4 Camera::Update(InputManager* controller)
{
	if (mode == eCameraMode::Free)
	{
		HandleMouseInput(controller->mouseX, controller->mouseY);
	}
	HandleKeybordInput(controller);
	return CalculateView();
}

void Camera::InitTopDownCamera()
{
	mode = eCameraMode::TopDown;
}

void Camera::HandleMouseInput(double xpos, double ypos, bool constraintOnPitch)
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

	CalculateDirection(xoffset, yoffset, constraintOnPitch);
}

