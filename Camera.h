#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Window.h"


class Camera
{
private:
	float Yaw = -90.0f;
	float Pitch = 0.0f;
	float LastX = 650;
	float LastY = 600;
	float MoveSpeed = 200.f;
	bool FirstMouseMovement = true;


public:
	Camera(glm::vec3& camPos, glm::vec3& camFront, glm::vec3& camUp);
	void SetPos(glm::vec3& pos);
	void SetFront(glm::vec3& front);
	void SetUp(glm::vec3& up);
	glm::vec3 CameraPos;
	glm::vec3 CameraFront;
	glm::vec3 CameraUp;
	glm::mat4 CalculateView();
	void HandleMouseInput(double xpos, double ypos);
	void CalculateDirection(float xoffset, float yoffset);
	void SetMoveSpeed(float newSpeed);
	void HandleKeybordInput(GLFWwindow* window);
	glm::mat4 Update(Window& window);
};





#endif
