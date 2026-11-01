#pragma once
#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"

enum eLightType :uint8_t
{
    Directional,
    Spot,
    Point
};

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
    glm::vec3 scale = glm::vec3(1);
    eLightType type;
    
public:
    BaseLight();
    BaseLight(int index, eLightType type);
    void SetPosition(glm::vec3& pos);
    void SetColor(glm::vec3& color);
    void SetAmbient(glm::vec3& ambient);
    glm::vec3 GetAmbient();
    glm::vec3 GetDiffuse();
    glm::vec3 GetSpecular();
    virtual void SetDirection(glm::vec3 dir);
    std::string SetBaseUniforms(Shader& shader);
    virtual void SetUniforms(Shader& shader);
    std::string GetLightStrucUniformName();
    virtual eLightType GetLightType();
    glm::vec3 GetWorldPosition();
};