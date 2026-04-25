#include <GLFW/glfw3.h>
#include <glad/glad.h> 
#include "Window.h"
#include "Shader.h"
#include "Renderer.h"
#include "ContentManager.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <iostream>


const unsigned int SCR_WIDTH = 1300;
const unsigned int SCR_HEIGHT = 1200;



void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


int main()
{
	glfwInit();

	Window window = Window(SCR_WIDTH, SCR_HEIGHT, "OpenGL");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    if (!window.CheckIfWindowWasCreated())
    {
        glfwTerminate();
        return -1;
    }


    glfwSetFramebufferSizeCallback(window.window, framebuffer_size_callback);
    window.SetViewPort(window.SCREEN_WIDTH, window.SCREEN_HEIGHT);

    Shader basicShader = ContentManager::LoadShader("basicVertexShader.vert", "basicFragmentShader.frag", "basicShader");
    ContentManager::InitColors();
    Renderer renderer = Renderer();
    glm::vec3 translation = glm::vec3(0.0f, 0.0f, -2.5f);
    glm::vec3 scale = glm::vec3(1.f);
    glm::vec3 rotation = glm::vec3(1.0f);
    glm::vec3 rotationAxis = glm::vec3(1.f);
    glm::vec3 color = ContentManager::GetColor("red");


    while (!glfwWindowShouldClose(window.window))
    {
        double xpos, ypos;
        glfwGetCursorPos(window.window, &xpos, &ypos); // Retrieves position relative to the content area
        translation.x = xpos / SCR_WIDTH;
        translation.y = (ypos / SCR_HEIGHT) * -1;

        std::cout << "Translation x:" << translation.x << std::endl;
        std::cout << "Translation y:" << translation.x << std::endl;

        renderer.view = glm::mat4(1.0f);
        renderer.view = glm::translate(renderer.view, glm::vec3(translation.x, translation.y, -1.5f));

        renderer.projection = glm::mat4(1.0f);
        renderer.projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);


        window.ChangeBackgroundColor(0.f, 0.f, 0.f, 1.0f);
        renderer.Draw(translation, scale, rotation, 10.f, color, basicShader);
        window.Update();
    }

    glfwTerminate();
    return 0;
}

