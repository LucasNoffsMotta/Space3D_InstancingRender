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
    ContentManager::LoadModel("D:/Projetos/c++/OpenGL/Assets/WorldFloor/Untitled.obj", "terrain", objID);
    ContentManager::LoadModel("D:/Projetos/c++/OpenGL/Assets/LancerEvo/evo_blendswap.obj", "object", objID++);
    ContentManager::LoadModel("D:/Projetos/c++/OpenGL/Assets/LancerEvo/evo_blendswap.obj", "object", objID++);
}

void SceneManager::LoadGlobalLigths()
{
    glm::vec3 pos = glm::vec3(9, 0, 3);
    glm::vec3 color = glm::vec3(0.01);

    for (int i = 0; i < ContentManager::MAX_POINT_LIGHTS; i++)
    {
        ContentManager::AddPointLight(i);
        ContentManager::PointLights[std::to_string(i)]->SetColor(color);
        ContentManager::PointLights[std::to_string(i)]->SetPosition(pos);
        pos.x -= 100;
        color.x -= 0.1;

    }

    glm::vec3 direction = glm::vec3(-0.2f, -1.0f, -0.3f);
    glm::vec3 ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    glm::vec3 diff = glm::vec3(0.4f, 0.4f, 0.4f);
    glm::vec3 spec = glm::vec3(0.5f, 0.5f, 0.5f);

    for (int i = 0; i < 1; i++)
    {
        ContentManager::AddDirectionalLight(i);
        ContentManager::DirectionalLights[std::to_string(i)]->SetDirection(direction);
        ContentManager::DirectionalLights[std::to_string(i)]->SetSpecular(spec);
        ContentManager::DirectionalLights[std::to_string(i)]->SetDiffuse(diff);
        ContentManager::DirectionalLights[std::to_string(i)]->SetAmbient(ambient);
    }

    glm::vec3 pos = glm::vec3(10, -1000, 0);
    glm::vec3 direction = glm::vec3(0, -1, 0);
    glm::vec3 color = glm::vec3(0.3, 0, 0.3);

    for (int i = 0; i < ContentManager::MAX_POINT_LIGHTS; i++)
    {
        ContentManager::AddSpotLight(i);
        ContentManager::SpotLights[std::to_string(i)]->SetColor(color);
        ContentManager::SpotLights[std::to_string(i)]->SetPosition(pos);
        ContentManager::SpotLights[std::to_string(i)]->SetDirection(direction);
        pos.x -= 30;
        color.z -= 0.1;
    }
}

void SceneManager::LoadSceneTree()
{
    //TODO: Start Root Node passing all the models, shaders and lights
}

void SceneManager::SetUpSceneNode(SceneNode* node)
{
    //TODO: Recursive method to construnct each node
}

void SceneManager::SetUpSceneProjection(glm::mat4& projection)
{
    
}

void SceneManager::RenderScene()
{
    RootNode->Render();
}


