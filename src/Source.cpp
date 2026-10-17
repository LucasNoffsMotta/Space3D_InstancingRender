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




void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


int main()
{
	glfwInit();

	Window window = Window(ContentManager::SCR_WIDTH, ContentManager::SCR_HEIGHT, "Void Engine");
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

    glfwGetFramebufferSize(window.window, &ContentManager::FRAMEBUFFER_SCREEN_SIZE_X, &ContentManager::FRAMEBUFFER_SCREEN_SIZE_Y);
    glfwSetFramebufferSizeCallback(window.window, framebuffer_size_callback);



    window.SetViewPort(ContentManager::FRAMEBUFFER_SCREEN_SIZE_X, ContentManager::FRAMEBUFFER_SCREEN_SIZE_Y);


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //glEnable(GL_CULL_FACE);

    float dt = 0.f;
    float lastFrame = 0.f;
    float camSpeed = 10.f;


    SceneManager scene = SceneManager();
    scene.InitScene();

    //renderer.InitScreenQuadVAO();

    while (!glfwWindowShouldClose(window.window))
    {
        //Per frame logic
        TimeHelper::Update();
        TimeHelper::ShowFps();

        float currentFrame = glfwGetTime();
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;

      
        scene.RenderScene(window);

        //Important:
        //For the framebuffer work properly, it is necessary to set get the screen size in pixels and pass it on the gl calls (texture, generate framebuffer, viewport and projection matrix), otherwise the logic size will be different of the actual framebuffer size

        window.Update();
    }

    glfwTerminate();     
    return 0;
}

