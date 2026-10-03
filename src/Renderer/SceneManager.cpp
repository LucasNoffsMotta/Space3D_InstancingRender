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

    //
}

void SceneManager::LoadSceneTree()
{
}

void SceneManager::SetUpSceneNode(SceneNode* node)
{
}

void SceneManager::SetUpSceneProjection(glm::mat4& projection)
{
    

}
