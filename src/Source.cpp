#include <GLFW/glfw3.h>
#include <glad/glad.h> 
#include "OpenGL/Window.h"
#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"
#include "Helper/ContentManager.h"
#include "Renderer/Camera.h"
#include "Renderer/Texture.h"
#include <iostream>
#include "Helper/TimeHelper.h"
#include "Misc/Projectile.h"
#include <vector>
#include "Renderer/SceneManager.h"


const unsigned int SCR_WIDTH = 1920;
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
    ContentManager::SetMainWindow(window.window);

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


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

  
    float dt = 0.f;
    float lastFrame = 0.f;
    float camSpeed = 10.f;

    SceneManager scene = SceneManager();
    scene.InitScene();

    while (!glfwWindowShouldClose(window.window))
    {
        window.ChangeBackgroundColor(0.f, 0.f, 0.f, 1.0f);
        TimeHelper::Update();
        TimeHelper::ShowFps();

        float currentFrame = glfwGetTime();
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;
        scene.RenderScene();
       window.Update();
    }

    glfwTerminate();     
    return 0;
}

