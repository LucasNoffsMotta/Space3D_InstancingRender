#pragma once

#include "glm/glm.hpp"
#include "../OpenGL/VAO.h"
#include "../OpenGL/EBO.h"
#include <vector>
#include "Texture.h"
#include "Shader.h"
#include "string.h"


struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh
{
private:
    VAO vao;
    EBO ebo;
    VBO vbo;
    void setupMesh();
    unsigned int VAO, VBO, EBO;

public:
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures);
    void Draw(Shader& shader);


};