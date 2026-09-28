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

//TODOS
/* 
* REFACTOR THE RENDERER!!!
    Stencil testing
*  Get Mouse Click on floor + rotate toards direction + move (Click and move)
*  Shadows / Gamma Correction
*  Create a scene class (scene objects, scene origin, etc)
*  Smoother mouse input
*  Add simple gravity that will act on the models!
*  Should be able to render using the same shader but without receiving light uniforms
*  Should be easy to switch between shaders
*  Should be easy to light on / light of
*  Change between different camera types
*  Async model loading
*  UI for level edit
*  Test case: make a object that can be moved using mouse clicks with top-down view (including rotation)
*/

//1 unit = 1 meter!

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
        "src/Shader/outline.frag",
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

    Shader outlineShader = ContentManager::LoadShader(
        "src/Shader/model.vert",
        "src/Shader/outline.frag",
        "outlineShader"
    );


    //Texture woodenFloor = Texture("D:/Projetos/c++/OpenGL/Assets/woodenFloor.jpg");
    ContentManager::LoadTexture("D:/Projetos/c++/OpenGL/Assets/woodenFloor.jpg", "woodenFloor");
    ContentManager::LoadTexture("D:/Projetos/c++/OpenGL/Assets/container2.png", "conteiner");
    ContentManager::LoadTexture("D:/Projetos/c++/OpenGL/Assets/container2_specular.png", "conteiner_specular");

    ContentManager::Textures["woodenFloor"]->SetTextureType(eTextureType::Diffuse);
    ContentManager::Textures["conteiner"]->SetTextureType(eTextureType::Diffuse);
    ContentManager::Textures["conteiner_specular"]->SetTextureType(eTextureType::Specular);



    ContentManager::LoadModel("D:/Projetos/c++/OpenGL/Assets/WorldFloor/Untitled.obj", "bloor");
    ContentManager::LoadModel("D:/Projetos/c++/OpenGL/Assets/LancerEvo/evo_blendswap.obj", "car");
    ContentManager::LoadModel("D:/Projetos/c++/OpenGL/Assets/LancerEvo/evo_blendswap.obj", "aar2");






    //ContentManager::LoadModel("D:/Projetos/c++/OpenGL/Assets/PinkCube/PinkCube.obj", "pinkCube");
    //ContentManager::LoadModel("D:/Projetos/c++/OpenGL/Assets/Village/house2.obj", "village");
    //

    //ContentManager::LoadModel("D:/Projetos/c++/OpenGL/Assets/SoccerStadium/SoccerArena.obj", "room");


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
    glm::vec3 modelPosTwo = glm::vec3(0.0f, 2.5f, 0);
    glm::vec3 modelPos3 = glm::vec3(0, 2.5f, 6);
    glm::vec3 sceneOrigin = glm::vec3(0.0f, 0.f, 0);
    Camera cam = Camera(camPos, camFront, camUp);
    ContentManager::AddCamera(&cam, "main");

    glm::vec3 baseScale = glm::vec3(1);
    glm::vec3 floorScale = glm::vec3(1);
    glm::vec3 largeScale = glm::vec3(10);

    //Model setup:
    // ContentManager::Models["room"]->SetWorldPosition(modelPosTwo);
    // ContentManager::Models["room"]->SetScale(baseScale);

    ContentManager::Models["bloor"]->SetWorldPosition(sceneOrigin);
    ContentManager::Models["bloor"]->SetScale(floorScale);
    ContentManager::Models["bloor"]->outline = false;

    ContentManager::Models["car"]->SetWorldPosition(modelPosTwo);
    ContentManager::Models["car"]->SetScale(baseScale);
    ContentManager::Models["car"]->SetRotationAngle(270);
    ContentManager::Models["car"]->outline = true;

    ContentManager::Models["aar2"]->SetWorldPosition(modelPos3);
    ContentManager::Models["aar2"]->SetScale(baseScale);
    ContentManager::Models["aar2"]->SetRotationAngle(270);
    ContentManager::Models["aar2"]->outline = true;

  /*  ContentManager::Models["pinkCube"]->SetWorldPosition(floorPos);
    ContentManager::Models["pinkCube"]->SetScale(largeScale);*/

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


    //ContentManager::Models["car"]->AttatchCamera(ContentManager::Cameras["main"], 16);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    //glStencilOpSeparate(GL_FRONT_AND_BACK, GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    while (!glfwWindowShouldClose(window.window))
    {
        window.ChangeBackgroundColor(0.f, 0.f, 0.f, 1.0f);
        ContentManager::Controllers["main"]->GetInput(window.window);
        TimeHelper::Update();
        TimeHelper::ShowFps();

        float currentFrame = glfwGetTime();
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;

        renderer.view = cam.Update(window, ContentManager::Controllers["main"]);
        //renderer.DrawAimDot(glm::vec3(0.01f, 0.01f, 0.01f), aimDotColor, aimDotShader, SCR_WIDTH, SCR_HEIGHT);
       //renderer.DrawInstances(instances, *ContentManager::Textures["conteiner"], *ContentManager::Textures["conteiner_specular"], scale, rotationAxis, 1.f, ContentManager::GetColor("white"), instancedLayoutShader);   // -> Draw instances by layout
       //renderer.Draw(glm::vec3(500, 0, 0), *ContentManager::Textures["woodenFloor"], glm::vec3(5000, 1, 5000), rotationAxis, 1.f, ContentManager::GetColor("white"), obj3DShader);
       //renderer.DrawScene(assimpShader, outlineShader);
        renderer.DrawStencilModelsTest(assimpShader, outlineShader);
       // renderer.DrawModel(*ContentManager::Models["car"], modelPosTwo, glm::vec3(1), outlineShader);
       //ContentManager::Models["car"]->Update(ContentManager::Controllers["main"]);
       //renderer.DrawModel(*ContentManager::Models["car"], modelPosTwo, glm::vec3(2), outlineShader);
       window.Update();
    }

    glfwTerminate();     
    return 0;
}

