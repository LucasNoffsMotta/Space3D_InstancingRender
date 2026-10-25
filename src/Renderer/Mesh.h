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
    glm::vec3 Position = glm::vec3(1);
    glm::vec3 Normal = glm::vec3(1);;
    glm::vec2 TexCoords = glm::vec2(1);;
};

class Mesh
{
private:
    VAO vao;
    EBO ebo;
    VBO vbo;
    void setupMesh(int layouts=3);
    unsigned int VAO, VBO, EBO;
public:
    int GetVAO();
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    Material material;
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures, glm::vec4& color, float shininess, float ior, int layouts = 3);
    void Draw(Shader& shader);
    void DrawInstanced(Shader& shader, int amount);
};