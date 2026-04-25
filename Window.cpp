#include "Window.h"

Window::Window(int width, int height, std::string title)
{
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(window);
}

bool Window::CheckIfWindowWasCreated()
{
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return false;
    }

    else
    {
        std::cout << "Window created" << std::endl;
    }

    return true;
}

void Window::framebuffer_size_callback()
{
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Window::SetViewPort(int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::Update()
{
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void Window::ChangeBackgroundColor(float r, float g, float b, float alpha)
{
    glClearColor(r, g, b, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

int Window::CloseRequest() const
{
    return glfwWindowShouldClose(window);
}