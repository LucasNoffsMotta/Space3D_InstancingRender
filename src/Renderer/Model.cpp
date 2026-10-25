#include "Model.h"
#include "../Helper/ContentManager.h"


Model::Model()
{
}

void Model::Draw(Shader& shader)
{
    if (useInstanced)
    {
        DrawInstanced(shader, instancesAmmount);
        return;
    }

	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].Draw(shader);
}


void Model::DrawInstanced(Shader& shader, int amount)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].DrawInstanced(shader, amount);
}



void Model::SetUseInstanced(int amount)
{
    useInstanced = true;
    instancesAmmount = amount;
    SetUpMeshesInstancedVao(instancesAmmount);
}

void Model::loadModel(std::string path)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_SortByPType | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));

    }

    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    glm::vec4 meshColor = glm::vec4(0);
    float shininess;
    float ior = 0.f;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // process vertex positions, normals and texture coordinates

        vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        
        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }

        else
        {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }
        //std::cout << "Processing mesh" << std::endl;
        vertices.push_back(vertex);
    }
    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }


    
    // process material
    if (mesh->mMaterialIndex >= 0)
    {
        aiColor4D color(0.f, 0.f, 0.f, 1.f);
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        float opacity;

        if (AI_SUCCESS != aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess))
        {
            shininess = 20.f;
        }

        if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, color))
        {
            meshColor.x = color.r;
            meshColor.y = color.g;
            meshColor.z = color.b;
        }

        if (AI_SUCCESS == material->Get(AI_MATKEY_REFRACTI, ior))
        {
            ior = 1 / ior;
        }

        if (AI_SUCCESS == material->Get(AI_MATKEY_OPACITY, opacity))
        {
            meshColor.a = opacity;
        }
        
        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, eTextureType::Diffuse);

        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, eTextureType::Specular);

        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh
    (vertices, indices, textures, meshColor, shininess, ior);
}

void Model::Load2DQuadTextureMesh(std::string filePath)
{
    std::vector<Vertex> vertices = LoadCustomPrimitiveMesh(ePrimitive::Quad);
    std::vector<Texture> textures;

    textures.push_back(Texture(filePath.c_str(), false, true));
    textures[0].SetTextureType(eTextureType::Diffuse);

    glm::vec4 color = glm::vec4(0);
    float shininess = 10.f;
    float ior = 0;

    std::vector<unsigned int> indices =  {  
    0, 1, 3,   
    1, 2, 3   
    };

    Mesh mesh = Mesh(vertices, indices, textures, color, shininess, ior);
    meshes.push_back(mesh);
}

void Model::Load2DQuadTextureMesh(Texture& texture)
{
    std::vector<Texture> textures;
    std::vector<Vertex> vertices = LoadCustomPrimitiveMesh(ePrimitive::Quad);

    textures.push_back(texture);

    glm::vec4 color = glm::vec4(0);
    float shininess = 10.f;
    float ior = 0;

    std::vector<unsigned int> indices = {
    0, 1, 3,
    1, 2, 3
    };

    Mesh mesh = Mesh(vertices, indices, textures, color, shininess, ior);
    meshes.push_back(mesh);
}

void Model::Load3DCubeVertices(Texture& texture)
{
    std::vector<Vertex> vertices = LoadCustomPrimitiveMesh(ePrimitive::Cube);

    std::vector<unsigned int> indices = {
        // Back face (-Z)
        0, 1, 2,
        2, 3, 0,

        // Left face (-X)
        1, 5, 4,
        4, 0, 1,

        // Right face (+X)
        2, 6, 7,
        7, 3, 2,

        // Front face (+Z)
        5, 6, 7,
        7, 4, 5,

        // Top face (+Y)
        0, 3, 7,
        7, 4, 0,

        // Bottom face (-Y)
        1, 5, 6,
        6, 2, 1
    };

    std::vector<Texture> textures;
    textures.push_back(texture);
    glm::vec4 color = glm::vec4(0);
    float s = 1.f;

    Mesh mesh = Mesh(vertices, indices, textures, color, s, 1);

    meshes.push_back(mesh);
}

//TODO: NEED TO FIX THE TEXTURE COORS ON A UNTEXTURED MODEL FROM BLENDER
void Model::SetNewTexturelForSingleMesh(int meshIndex, int textureIndex, Texture& newTexture)
{
    if (meshes.at(meshIndex).material.textures.size() <= textureIndex)
    {
        meshes.at(meshIndex).material.textures.push_back(newTexture);
        return;
    }
    meshes.at(meshIndex).material.textures[textureIndex] = newTexture;
}

void Model::PushNewTexture(Texture& newTexture)
{
    for (auto& mesh : meshes)
    {
        mesh.material.textures.push_back(newTexture);
    }
}

void Model::SetUpMeshesInstancedVao(int amount)
{
    InitInstancesTranslations();
    CreateInstancedModelMatrices(amount);

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

    for (int i = 0; i < meshes.size(); i++)
    {
        unsigned int vao = meshes[i].GetVAO();
        glBindVertexArray(vao);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);
        glBindVertexArray(0);
    }
}

void Model::InitInstancesTranslations()
{
    srand(static_cast<unsigned int>(glfwGetTime())); // initialize random seed

    instancesTranslationPtr = new glm::vec3[instancesAmmount];

    glm::vec3 pos = glm::vec3(-20, 1.8, -20);
    int index = 0;
    for (int i = 0; i < instancesAmmount; i++)
    {
        instancesTranslationPtr[i] = pos;
        float displacement = (float)(rand()) / (float)(RAND_MAX);
        pos.z += (displacement);

        if (pos.z > 10)
        {
            pos.z = -20;
            pos.x += (displacement);
        }
    }
}

std::vector<Vertex> Model::LoadCustomPrimitiveMesh(ePrimitive primitive)
{
    std::vector<Vertex> vertices;

    if (primitive == ePrimitive::Quad)
    {
        Vertex vert1;
        Vertex vert2;
        Vertex vert3;
        Vertex vert4;

        vert1.Position = glm::vec3(0.5f, 0.5f, 0.0f);
        vert1.TexCoords = glm::vec2(1.f, 1.0f);

        vert2.Position = glm::vec3(0.5f, -0.5f, 0.0f);
        vert2.TexCoords = glm::vec2(1.0f, 0.0f);

        vert3.Position = glm::vec3(-0.5f, -0.5f, 0.0f);
        vert3.TexCoords = glm::vec2(0.0f, 0.0f);

        vert4.Position = glm::vec3(-0.5f, 0.5f, 0.0f);
        vert4.TexCoords = glm::vec2(0.0f, 1.0f);


        vertices.push_back(vert1);
        vertices.push_back(vert2);
        vertices.push_back(vert3);
        vertices.push_back(vert4);
    }


    //SHIT CODE!
    // Done in a rush.. if it works:
    //To improve: Might create a method that receive an array of float and an vertex offset (similar to set attrib array) to create the Vertices vector 
    else if (primitive == ePrimitive::Cube)
    {
        float skyboxVertices[] = {
            // Positions
            -1.0f,  1.0f, -1.0f, // 0: Top-left-back
            -1.0f, -1.0f, -1.0f, // 1: Bottom-left-back
             1.0f, -1.0f, -1.0f, // 2: Bottom-right-back
             1.0f,  1.0f, -1.0f, // 3: Top-right-back
            -1.0f,  1.0f,  1.0f, // 4: Top-left-front
            -1.0f, -1.0f,  1.0f, // 5: Bottom-left-front
             1.0f, -1.0f,  1.0f, // 6: Bottom-right-front
             1.0f,  1.0f,  1.0f  // 7: Top-right-front
        };

        Vertex vert1 = Vertex();
        Vertex vert2 = Vertex();
        Vertex vert3 = Vertex();
        Vertex vert4 = Vertex();
        Vertex vert5 = Vertex();
        Vertex vert6 = Vertex();
        Vertex vert7 = Vertex();
        Vertex vert8 = Vertex();

        vert1.Position = glm::vec3(-1.0, 1.f, -1.f);
        vert2.Position = glm::vec3(-1.0f, -1.0f, -1.0f);
        vert3.Position = glm::vec3(1.0f, -1.0f, -1.0f);
        vert4.Position = glm::vec3(1.0f, 1.0f, -1.0f);
        vert5.Position = glm::vec3(-1.0f, 1.0f, 1.0f);
        vert6.Position = glm::vec3(-1.0f, -1.0f, 1.0f);
        vert7.Position = glm::vec3(1.0f, -1.0f, 1.0f);
        vert8.Position = glm::vec3(1.0f, 1.0f, 1.0f);

        vertices.push_back(vert1);
        vertices.push_back(vert2);
        vertices.push_back(vert3);
        vertices.push_back(vert4);
        vertices.push_back(vert5);
        vertices.push_back(vert6);
        vertices.push_back(vert7);
        vertices.push_back(vert8);
    }

     return vertices;
}

Texture& Model::CreateSkyBox(std::string cubemapFolder)
{
    //Will remove thast shit later
    std::vector<std::string> faces
    {
        cubemapFolder + "/right.jpg",
        cubemapFolder + "/left.jpg",
        cubemapFolder + "/top.jpg",
        cubemapFolder + "/bottom.jpg",
        cubemapFolder + "/front.jpg",
        cubemapFolder + "/back.jpg"
    };

    Texture cubeMap = Texture();
    cubeMap.GenerateCubemapTexture(faces);
    Load3DCubeVertices(cubeMap);
    return cubeMap;
}


void Model::CreateInstancedModelMatrices(int amount)
{
    modelMatrices = new glm::mat4[amount];


    for (int i = 0; i < amount; i++)
    {
        glm::vec3 trans = *instancesTranslationPtr;
        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model, trans);
        model = glm::scale(model, glm::vec3(1));
        modelMatrices[i] = model;
        //float scale = static_cast<float>((rand() % 20) / 100.0 + 0.05);
        //model = glm::scale(model, glm::vec3(scale));
        instancesTranslationPtr++;
    }
}

void Model::RotatePitch(float offSet)
{
    Pitch += offSet;
    if (Pitch >= 360) Pitch = 0;
}

void Model::RotateYaw(float offSet)
{
    Yaw += offSet;
    if (Yaw >= 360) Yaw = 0;
}

void Model::RotateRoll(float offSet)
{
    Roll += offSet;
    if (Roll >= 360) Roll = 0;
}


std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, eTextureType eType)
{
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        bool skip = false;
        auto file = str.C_Str();

        for (unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }

        if (!skip)
        {
            std::string path = directory + '/' + std::string(file);
            Texture text = Texture(path.c_str(), false);
            text.SetTextureType(eType);
            text.path = str.C_Str();
            textures.push_back(text);
            textures_loaded.push_back(text);
        }
    }
    return textures;
}


