#include "Game/Camera.h"
#include "Helper/TimeHelper.h"

Camera::Camera(glm::vec3& camPos, glm::vec3& camFront, glm::vec3& camUp)
{
	CameraPos = camPos;
	CameraFront = camFront;
	CameraUp = camUp;
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
}

void Camera::SetMoveSpeed(float newSpeed)
{
	MoveSpeed = newSpeed;
}

void Camera::HandleKeybordInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		//CameraPos.x += (MoveSpeed * CameraFront.x) * TimeHelper::GetDeltaTime();
		//CameraPos.z += (MoveSpeed * CameraFront.z) * TimeHelper::GetDeltaTime();
		CameraPos += (MoveSpeed * CameraFront) * TimeHelper::GetDeltaTime();
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		//CameraPos.x -= (MoveSpeed * CameraFront.x) * TimeHelper::GetDeltaTime();
		//CameraPos.z -= (MoveSpeed * CameraFront.z) * TimeHelper::GetDeltaTime();
		CameraPos -= (MoveSpeed * CameraFront) * TimeHelper::GetDeltaTime();
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		CameraPos -= (glm::normalize(glm::cross(CameraFront, CameraUp)) * MoveSpeed) * TimeHelper::GetDeltaTime();
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		CameraPos += (glm::normalize(glm::cross(CameraFront, CameraUp)) * MoveSpeed) * TimeHelper::GetDeltaTime();
	}
}

glm::mat4 Camera::CalculateView()
{
	return glm::lookAt(CameraPos, CameraPos + CameraFront, CameraUp);
}

glm::mat4 Camera::Update(Window& window)
{
	double mouseX = 1;
	double mouseY = 1;
	glfwGetCursorPos(window.window, &mouseX, &mouseY);
	HandleMouseInput(mouseX, mouseY);
	HandleKeybordInput(window.window);
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
