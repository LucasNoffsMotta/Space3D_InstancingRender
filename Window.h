#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class Window
{
public:
	Window(int width, int height, std::string title);
	int  SCREEN_HEIGHT;
	int  SCREEN_WIDTH;
	GLFWwindow* window;
	void framebuffer_size_callback();
	bool CheckIfWindowWasCreated();
	void SetViewPort(int width, int height);
	void Update();
	void ChangeBackgroundColor(float r, float g, float b, float alpha);
	int CloseRequest() const;
};



#endif
