#include <GLFW/glfw3.h>
#include <glad/glad.h> 
#include "Window.h"
#include "Shader.h"
#include "Renderer.h"
#include "ContentManager.h"
#include <assimp/Importer.hpp>
#include "Camera.h"
#include <assimp/scene.h>

#include <iostream>
#include "TimeHelper.h"


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

    Shader instancedUniformShader = ContentManager::LoadShader("instancedUniformVertex.vert", "basicFragmentShader.frag", "instancedUniform");
    Shader instancedLayoutShader = ContentManager::LoadShader("instancedLayoutVertex.vert", "basicFragmentShader.frag", "instancedLayout");
    Shader basicShader = ContentManager::LoadShader("basicVertex.vert", "basicFragmentShader.frag", "basicShader");


    ContentManager::InitColors();
    Renderer renderer = Renderer();

    glm::vec3 scale = glm::vec3(1.f);
    glm::vec3 rotation = glm::vec3(1.0f);
    glm::vec3 rotationAxis = glm::vec3(1.f);
    glm::vec3 color = ContentManager::GetColor("green");

    glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);
    Camera cam = Camera(camPos, camFront, camUp);

    float dt = 0.f;
    float lastFrame = 0.f;
    float camSpeed = 10.f;

    int amount = 10;

    renderer.SetInstancedTranslations(100);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window.window))
    {
        TimeHelper::Update();
        TimeHelper::ShowFps();
        float currentFrame = glfwGetTime();
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;
        renderer.view = cam.Update(window);
        window.ChangeBackgroundColor(0.f, 0.f, 0.f, 1.0f); 
        renderer.DrawInstances(scale, rotationAxis, 1.f, color, instancedUniformShader);       
        window.Update();
    }

    glfwTerminate();     
    return 0;
}

