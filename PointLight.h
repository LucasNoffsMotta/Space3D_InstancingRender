#pragma once
#include <glm/glm.hpp>
#include <Render/Shader.h>
#include "Helper/ContentManager.h"
#include <Render/Renderer.h>

class PointLight
{
private:
    glm::vec3 position = glm::vec3(1);
    glm::vec3 color = glm::vec3(1.0, 1.0, 0.0);
    glm::vec3 ambient = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::vec3 diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);
    float constant = 1;
    float linear = 0.09f;
    float quadratic = 0.032f;
    int lightIndex;
    glm::mat4 model;
    glm::vec3 scale = glm::vec3(0.1);

public:

    PointLight(int index);
    void SetPosition(glm::vec3& pos);
    void SetColor(glm::vec3& color);
    void SetAmbient(glm::vec3& ambient);
    void SetUniforms(Shader& shader);
    void Draw(Shader& shader, Renderer& renderer);


    //shader.SetUniform3fv("pointLight[0].position", pos1);
    //shader.SetUniform3fv("pointLight[0].color", glm::vec3(1.0, 0.0, 0.0));
    //shader.SetUniform3fv("pointLight[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
    //shader.SetUniform3fv("pointLight[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
    //shader.SetUniform3fv("pointLight[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
    //shader.SetUniformFloat("pointLight[0].constant", 1.0f);
    //shader.SetUniformFloat("pointLight[0].linear", 0.09f);
    //shader.SetUniformFloat("pointLight[0].quadratic", 0.032f);
};