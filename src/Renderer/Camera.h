#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../OpenGL/Window.h"
#include "../Helper/InputManager.h"
#include "../Helper/eCameraMode.h"


class SpotLight;


class Camera
{
private:
	float Yaw = -90.0f;
	float Pitch = 0.0f;
	float LastX = 650;
	float LastY = 600;
	float MoveSpeed = 400;
	bool FirstMouseMovement = true;
	eCameraMode mode = eCameraMode::Free;
	glm::vec3 topDownDirection = glm::vec3(-0.00205945, -0.765213 ,-0.643773);
	glm::vec3 topDownPosition = glm::vec3(663.234, 1020.36, 804.61);


public:
	float cameraLight = 1;
	void SetSpotLight();
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
	void HandleKeybordInput(InputManager* controller);
	glm::mat4 Update(Window& window, InputManager* controller);
};





#endif
