#include "TimeHelper.h"
#include <GLFW/glfw3.h>
#include <iostream>

float TimeHelper::CurrentFrame = 0.f;
float TimeHelper::LastFrame = 0.f;
float TimeHelper::dt = 0.f;


float TimeHelper::GetDeltaTime()
{
	return dt;
}

void TimeHelper::Update()
{
	CurrentFrame = glfwGetTime();
	dt = CurrentFrame - LastFrame;
	LastFrame = CurrentFrame;
}

void TimeHelper::ShowFps()
{
	float fps = 1 / dt;
	std::cout << "FPS: " << fps << std::endl;
}

