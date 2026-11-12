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
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
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

    ContentManager::SetGlobalRenderMode(eRenderMode::NoLights);
    ContentManager::SetPostProcessEffect(ePostProcessEffect::NightVision);

    ImGui::CreateContext();


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);

    float dt = 0.f;
    float lastFrame = 0.f;
    float camSpeed = 10.f;


    //Dear ImGui init
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window.window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();


    SceneManager scene = SceneManager();
    scene.InitScene();

    while (!glfwWindowShouldClose(window.window))
    {
        //Per frame logic
        TimeHelper::Update();
        TimeHelper::ShowFps();

        float currentFrame = glfwGetTime();
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow(); // Show demo window! :)

      
        scene.RenderScene(window);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //Important:
        //For the framebuffer work properly, it is necessary to set get the screen size in pixels and pass it on the gl calls
        // (texture, generate framebuffer, viewport and projection matrix), 
        // otherwise the logic size will be different of the actual framebuffer size

        window.Update();

                // ...

    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();     
    return 0;
}

