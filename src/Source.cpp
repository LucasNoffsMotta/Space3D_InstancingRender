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


/*
* 
*  TODO: Add more properties to Model class (translation, rotation, origin, etc!);
*  Make a system to get more soft inputs (trheshold) 
*/



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

    Shader instancedUniformShader = ContentManager::LoadShader(
        "src/Shader/instancedUniformVertex.vert",
        "src/Shader/frag.frag",
        "instancedUniform");

    Shader instancedLayoutShader = ContentManager::LoadShader(
        "src/Shader/instancedLayoutVertex.vert",
        "src/Shader/frag.frag",
        "instancedLayout");

    Shader basicShader = ContentManager::LoadShader(
        "src/Shader/basicVertex.vert",
        "src/Shader/frag.frag",
        "basicShader");

    Shader aimDotShader = ContentManager::LoadShader(
        "src/Shader/2dVertex.vert",
        "src/Shader/SimpleColorFragmentShader.frag",
        "aimDotShader");

    Shader obj3DShader = ContentManager::LoadShader(
        "src/Shader/object3DFragment.vert",
        "src/Shader/frag.frag",
        "object3DShader"
    );

    Shader assimpShader = ContentManager::LoadShader(
        "src/Shader/model.vert",
        "src/Shader/frag.frag",
        "assimpShader"
    );

    //Texture woodenFloor = Texture("D:/Projetos/c++/OpenGL/Assets/woodenFloor.jpg");
    ContentManager::LoadTexture("D:/Projetos/c++/OpenGL/Assets/woodenFloor.jpg", "woodenFloor");
    ContentManager::LoadTexture("D:/Projetos/c++/OpenGL/Assets/container2.png", "conteiner");
    ContentManager::LoadTexture("D:/Projetos/c++/OpenGL/Assets/container2_specular.png", "conteiner_specular");

    ContentManager::Textures["woodenFloor"]->SetTextureType(eTextureType::Diffuse);
    ContentManager::Textures["conteiner"]->SetTextureType(eTextureType::Diffuse);
    ContentManager::Textures["conteiner_specular"]->SetTextureType(eTextureType::Specular);

    //ContentManager::LoadModel("D:/Projetos/c++/OpenGL/Assets/3D/backpack.obj", "backpack");
    ContentManager::LoadModel("D:/Projetos/c++/OpenGL/Assets/Village/house2.obj", "village");
    ContentManager::LoadModel("D:/Projetos/c++/OpenGL/Assets/WorldFloor/Untitled.obj", "floor");

    ContentManager::AddController("main");


    ContentManager::InitColors();
    Renderer renderer = Renderer();

    glm::vec3 scale = glm::vec3(10000.f);
    glm::vec3 bulletScale = glm::vec3(0.5f);
    glm::vec3 rotation = glm::vec3(1.0f);
    glm::vec3 rotationAxis = glm::vec3(1.f);
    glm::vec3 planetColor = ContentManager::GetColor("yellow");
    glm::vec3 asteroidColor = ContentManager::GetColor("green");
    glm::vec3 aimDotColor = ContentManager::GetColor("red");


    glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 modelPosOne = glm::vec3(0.0f, 100.0f, 100.0f);
    glm::vec3 modelPosTwo = glm::vec3(0.0f, -400.0f, 100.0f);
    glm::vec3 floorPos = glm::vec3(0.0f, -380.0f, 100.0f);
    Camera cam = Camera(camPos, camFront, camUp);
    ContentManager::AddCamera(&cam, "main");

    float dt = 0.f;
    float lastFrame = 0.f;
    float camSpeed = 10.f;

    int instances = 100;
    renderer.SetInstancedTranslations(instances);
    renderer.SetInstancesBuffers(instances);
    renderer.InitAimDotRenderData();
    renderer.InitBulletRenderData();
    renderer.bulletShoot = false;
    std::vector<Projectile> projectiles;

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window.window))
    {
        ContentManager::Controllers["main"]->GetInput(window.window);
        TimeHelper::Update();
        TimeHelper::ShowFps();
        float currentFrame = glfwGetTime();
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;
        renderer.view = cam.Update(window, ContentManager::Controllers["main"]);

        window.ChangeBackgroundColor(0.f, 0.f, 0.f, 1.0f); 
        renderer.DrawAimDot(glm::vec3(0.01f, 0.01f, 0.01f), aimDotColor, aimDotShader, SCR_WIDTH, SCR_HEIGHT);
        renderer.DrawInstances(instances, *ContentManager::Textures["conteiner"], *ContentManager::Textures["conteiner_specular"], scale, rotationAxis, 1.f, ContentManager::GetColor("white"), instancedLayoutShader);   // -> Draw instances by layout
        //renderer.Draw(glm::vec3(500, 0, 0), *ContentManager::Textures["woodenFloor"], glm::vec3(5000, 1, 5000), rotationAxis, 1.f, ContentManager::GetColor("white"), obj3DShader);
        renderer.DrawModel(*ContentManager::Models["village"], modelPosTwo, glm::vec3(100), assimpShader);
        renderer.DrawModel(*ContentManager::Models["floor"], floorPos, glm::vec3(100, 1, 100), assimpShader);

         for (const auto& [key, value] : ContentManager::PointLights) {
            value->DrawPointLight(obj3DShader, *ContentManager::Textures["woodenFloor"], renderer);
        }

       window.Update();
    }

    glfwTerminate();     
    return 0;
}

