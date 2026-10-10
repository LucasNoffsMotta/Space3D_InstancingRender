#pragma once
#include "Shader.h"
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../Helper/InputManager.h"
#include "Camera.h"


class Model
{


private:
    // model data

    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;


    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    void SetUpMeshesInstancedVao(int amount);
    void InitInstancesTranslations();

    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, eTextureType eType);


public:
    Model(const char* path)
    {
        loadModel(path);
    }

    Model();
    bool useInstanced;
    void Draw(Shader& shader);
    void DrawInstanced(Shader& shader, int amount);
    void CreateInstancedModelMatrices(int amount);

    //Instancing:
    glm::mat4* modelMatrices;  //Large object array 
    glm::vec3* instancesTranslationPtr;   //Large object array 
    int instancesAmmount;


    void SetUseInstanced(int amount);


};