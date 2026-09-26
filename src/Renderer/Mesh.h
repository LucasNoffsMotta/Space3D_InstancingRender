#pragma once

#include "glm/glm.hpp"
#include "../OpenGL/VAO.h"
#include "../OpenGL/EBO.h"
#include <vector>
#include "Texture.h"
#include "Shader.h"
#include "string.h"
#include "Material.h"


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
    Material material;
public:
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures, glm::vec3& color, float shininess);
    void Draw(Shader& shader);


};