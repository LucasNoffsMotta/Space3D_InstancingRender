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
    Model* terrain = ContentManager::LoadModel("D:/Projetos/c++/OpenGL/Assets/WorldFloor/Untitled.obj", "terrain", objID);
    Model* testModelOne = ContentManager::LoadModel("D:/Projetos/c++/OpenGL/Assets/LancerEvo/evo_blendswap.obj", "object", objID++);
    Model* testModelTwo = ContentManager::LoadModel("D:/Projetos/c++/OpenGL/Assets/LancerEvo/evo_blendswap.obj", "object", objID++);

    glm::vec3 test_pos1 = glm::vec3(0.0f, 2.5f, 0);
    glm::vec3 test_pos2 = glm::vec3(0, 2.5f, 6);

    terrain->doStencilTest = false;
    terrain->SetWorldPosition(sceneOrigin);
    terrain->SetScale(baseScale);

    testModelOne->SetWorldPosition(test_pos1);
    testModelOne->SetScale(baseScale);
    testModelOne->SetRotationAngle(270);
    testModelOne->doStencilTest = true;

    testModelOne->AttatchCamera(BaseCamera, 16);

    testModelTwo->SetWorldPosition(test_pos2);
    testModelTwo->SetScale(baseScale);
    testModelTwo->SetRotationAngle(270);
    testModelTwo->doStencilTest = true;
}

void SceneManager::LoadGlobalLigths()
{
    glm::vec3 pointPos = glm::vec3(9, 0, 3);
    glm::vec3 pointColor = glm::vec3(0.01);

    for (int i = 0; i < ContentManager::MAX_POINT_LIGHTS; i++)
    {
        ContentManager::AddPointLight(i);
        ContentManager::PointLights[std::to_string(i)]->SetColor(pointColor);
        ContentManager::PointLights[std::to_string(i)]->SetPosition(pointPos);
        pointPos.x -= 100;
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
    LoadShaderSingletons();
    LoadGlobalLigths();
    LoadCamera();
    LoadModelsAndSetPositions();
    LoadViewAndProjectionMatrices();
    LoadSceneTree(0);
    SetUpSceneNode(RootNode);
}

void SceneManager::LoadCamera()
{
    glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);

    BaseCamera = new Camera(camPos, camFront, camUp);
    ContentManager::AddCamera(BaseCamera, "main");
}

void SceneManager::LoadSceneTree(int levels)
{
    RootNode = new SceneNode(0);
    if (levels > 0)
    {
        AddNode(RootNode, 0, levels);
    }
}

void SceneManager::AddNode(SceneNode* parent, int level, int totalLevels)
{
    if (level < totalLevels)
    {
        SceneNode* node = new SceneNode(level);
        parent->AttatchChildNode(node);
        AddNode(node, level++, totalLevels);
    }
}

void SceneManager::SetUpSceneNode(SceneNode* node)
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

    for (int i = 0; i < ContentManager::Models["terrain"].size(); i++)
    {
        node->AttatchModel(ContentManager::Models["terrain"].at(i));
    }

    for (int i = 0; i < ContentManager::Models["object"].size(); i++)
    {
        node->AttatchModel(ContentManager::Models["object"].at(i));
    }

    node->SetShaderMap(RootShaderMap);
    node->SetProjectionMatrix(Projection);

    if (node->children.size() > 0)
    {
        for (int i = 0; i < node->children.size(); i++)
        {
            SetUpSceneNode(node->children.at(i));
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
    RootNode->UpdateNode();
}

void SceneManager::LoadViewAndProjectionMatrices()
{
    View = glm::mat4(1.0f);
    Projection = glm::mat4(1.0f);
    Projection = glm::perspective(glm::radians(45.0f), (float)1920 / 1200, 0.1f, 6000.f);
}


