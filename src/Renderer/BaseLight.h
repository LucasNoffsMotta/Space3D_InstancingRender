#pragma once
#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"


class BaseLight
{
protected:
    glm::vec3 position = glm::vec3(1);
    glm::vec3 color = glm::vec3(0.0, 0.0, 1.0);
    glm::vec3 ambient = glm::vec3(1, 1, 1);
    glm::vec3 diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);

    int lightIndex;
    glm::mat4 model = glm::mat4(1);
    glm::vec3 scale = glm::vec3(10);
    

public:
    BaseLight();
    BaseLight(int index);
    void SetPosition(glm::vec3& pos);
    void SetColor(glm::vec3& color);
    void SetAmbient(glm::vec3& ambient);
    std::string SetUniforms(Shader& shader, std::string shaderStruct);
    void Draw(Shader& shader, Texture& texture, Renderer& renderer);
};