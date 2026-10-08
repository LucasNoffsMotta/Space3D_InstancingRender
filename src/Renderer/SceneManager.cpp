#include "SceneManager.h"
#include "../Helper/ContentManager.h"



void SceneManager::LoadShaderSingletons()
{
    RootShaderMap[eRenderMode::Regular] = ContentManager::LoadShader(
        "src/Shader/model.vert",
        "src/Shader/frag.frag",
        "assimpShader"
    );

    RootShaderMap[eRenderMode::StencilMask] = ContentManager::LoadShader(
        "src/Shader/model.vert",
        "src/Shader/outline.frag",
        "outlineShader"
    );

    RootShaderMap[eRenderMode::WiredOn]  = ContentManager::LoadShader(
        "src/Shader/BoundBox.vert",
        "src/Shader/BoundBox.frag",
        "boundBoxShader"
    );
}

void SceneManager::LoadModelsAndSetPositions()
{
    int objID = 0;
    Model* carMesh = ContentManager::LoadModel("D:/Projetos/c++/OpenGL/Assets/LancerEvo/evo_blendswap.obj", "car");
    Model* terrainMes = ContentManager::LoadModel("D:/Projetos/c++/OpenGL/Assets/WorldFloor/Untitled.obj", "terrain");
    Model* hollowMesh = ContentManager::LoadModel("D:/Projetos/c++/OpenGL/Assets/HollowKnight/HollowKnightRig.obj", "hollow");
    Model* soldierMesh = ContentManager::LoadModel("D:/Projetos/c++/OpenGL/Assets/Soldier/WW2Panzergrenadier.obj","soldier");

    ContentManager::CreateEntity(STENCIL_TEST, carMesh, glm::vec3(0, 2.5, 0), glm::vec3(1), 270, true);
    ContentManager::CreateEntity(STENCIL_TEST, carMesh, glm::vec3(0, 2.5, 5), glm::vec3(1), 270, false);
    ContentManager::CreateEntity(STENCIL_TEST, hollowMesh, glm::vec3(7, 1.0, 1), glm::vec3(1), 270, false);
    ContentManager::CreateEntity(STENCIL_TEST, soldierMesh, glm::vec3(0, 1.0, 8), glm::vec3(0.02), 270, true);
    ContentManager::CreateEntity(NO_STENCIL_TEST, terrainMes, sceneOrigin, glm::vec3(1), 0, false);
}

void SceneManager::LoadGlobalLigths()
{
    glm::vec3 pointPos = glm::vec3(0, 5, 3);
    glm::vec3 pointColor = glm::vec3(0.8117, 0.3960f, 0.8784);
    //r = 0,5960
    //g = 0,2392
    //b = 0,6039

    for (int i = 0; i < ContentManager::MAX_POINT_LIGHTS; i++)
    {
        ContentManager::AddPointLight(i);
        ContentManager::PointLights[std::to_string(i)]->SetColor(pointColor);
        ContentManager::PointLights[std::to_string(i)]->SetPosition(pointPos);
        pointPos.x +=20;
        GlobalLights.push_back(ContentManager::PointLights[std::to_string(i)].get());
    }

    glm::vec3 directionalDir = glm::vec3(-0.2f, -1.0f, -0.3f);
    glm::vec3 ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    glm::vec3 diff = glm::vec3(0.4f, 0.4f, 0.4f);
    glm::vec3 spec = glm::vec3(0.5f, 0.5f, 0.5f);

    for (int i = 0; i < 1; i++)
    {
        ContentManager::AddDirectionalLight(i);
        ContentManager::DirectionalLights[std::to_string(i)]->SetDirection(directionalDir);
        ContentManager::DirectionalLights[std::to_string(i)]->SetSpecular(spec);
        ContentManager::DirectionalLights[std::to_string(i)]->SetDiffuse(diff);
        ContentManager::DirectionalLights[std::to_string(i)]->SetAmbient(ambient);
        GlobalLights.push_back(ContentManager::DirectionalLights[std::to_string(i)].get());
    }

    glm::vec3 spotPos = glm::vec3(10, -1000, 0);
    glm::vec3 direction = glm::vec3(0, -1, 0);
    glm::vec3 color = glm::vec3(0.3, 0, 0.3);

    for (int i = 0; i < ContentManager::MAX_POINT_LIGHTS; i++)
    {
        ContentManager::AddSpotLight(i);
        ContentManager::SpotLights[std::to_string(i)]->SetColor(color);
        ContentManager::SpotLights[std::to_string(i)]->SetPosition(spotPos);
        ContentManager::SpotLights[std::to_string(i)]->SetDirection(directionalDir);
        spotPos.x -= 30;
        color.z -= 0.1;
        GlobalLights.push_back(ContentManager::SpotLights[std::to_string(i)].get());
    }
}

void SceneManager::InitScene()
{
    InitHierarchyStructs();
    LoadEmptyTreeBasedOnLevels();
    LoadShaderSingletons();
    LoadGlobalLigths();
    LoadCamera();
    LoadModelsAndSetPositions();
    LoadViewAndProjectionMatrices();
    FillSceneTree(RootNode);
}

void SceneManager::LoadCamera()
{
    glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);

    BaseCamera = new Camera(camPos, camFront, camUp);
    ContentManager::AddCamera(BaseCamera, "main");
}

void SceneManager::LoadEmptyTreeBasedOnLevels()
{
    int level = 0;
    RootNode = new SceneNode(hierarchy[level].level);
    AddNode(RootNode, level);
}

void SceneManager::AddNode(SceneNode* node, int level)
{
    level++;
    if (level < hierarchy.size())
    {
        SceneNode* child = new SceneNode(hierarchy[level].level);
        node->AttatchChildNode(child);
        AddNode(child, level);
    }
}


void SceneManager::FillSceneTree(SceneNode* node)
{
    ContentManager::AddController("main");
    InputManager* rootController = ContentManager::Controllers["main"];
    rootController->windowReference = ContentManager::mainWindow;
    node->AttatchController(ContentManager::Controllers["main"]);

    node->AttatchCamera(BaseCamera);

    for (int i = 0; i < GlobalLights.size(); i++)
    {
        node->AttatchLight(GlobalLights[i]);
    }

    for (auto* m : ContentManager::Entities[node->level])
    {
        node->AttatchEntity(m);
    }

    node->SetShaderMap(RootShaderMap);
    node->SetProjectionMatrix(Projection);

    if (node->children.size() > 0)
    {
        for (int i = 0; i < node->children.size(); i++)
        {
            FillSceneTree(node->children.at(i));
        }
    }
}

void SceneManager::SetUpSceneProjection(glm::mat4& projection)
{
    RootShaderMap[eRenderMode::Regular]->Activate();
    RootShaderMap[eRenderMode::Regular]->SetUniformMatrix4fv("projection", projection);

    RootShaderMap[eRenderMode::StencilMask]->Activate();
    RootShaderMap[eRenderMode::StencilMask]->SetUniformMatrix4fv("projection", projection);

    RootShaderMap[eRenderMode::WiredOn]->Activate();
    RootShaderMap[eRenderMode::WiredOn]->SetUniformMatrix4fv("projection", projection);
}

void SceneManager::RenderScene()
{

    //Setup Lights
    RootNode->UpdateNode();
}

void SceneManager::LoadViewAndProjectionMatrices()
{
    View = glm::mat4(1.0f);
    Projection = glm::mat4(1.0f);
    Projection = glm::perspective(glm::radians(45.0f), (float)1920 / 1200, 0.1f, 6000.f);
}

void SceneManager::InitHierarchyStructs()
{
    hierarchy.push_back(HierarchyLevel(eHierarchyLevel::NO_STENCIL_TEST, 0));
    hierarchy.push_back(HierarchyLevel(eHierarchyLevel::STENCIL_TEST, 1));
}



