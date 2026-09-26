#pragma once
#include "Shader.h"
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
    Model(const char* path)
    {
        loadModel(path);
    }

    void Draw(Shader& shader);
    void SetWorldPosition(glm::vec3& newPos);
    void SetScale(glm::vec3& newScale);
    glm::vec3 GetWorldPosition();
    glm::vec3 GetScale();

private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;
    glm::vec3 worldPosition;
    glm::vec3 scale;


    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, eTextureType eType);
};