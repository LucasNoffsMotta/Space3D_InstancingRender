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
    glm::vec3 direction = glm::vec3(1.0f, 1.0f, 1.0f);

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
    glm::vec3& GetColor();
    glm::vec3& GetAmbient();
    glm::vec3& GetAmbientColor();
    glm::vec3& GetDiffuse();
    glm::vec3& GetSpecular();

    glm::vec4& GetVec4Direction();
    glm::vec4& GetVec4Ambient();
    glm::vec4& GetVec4AmbientColor();
    glm::vec4& GetVec4Diffuse();
    glm::vec4& GetVec4Specular();

    virtual void SetDirection(glm::vec3 dir);
    virtual glm::vec3& GetDirection();

    std::string SetBaseUniforms(Shader& shader);
    virtual void SetUniforms(Shader& shader);
    std::string GetLightStrucUniformName();
    virtual eLightType GetLightType();
    glm::vec3 GetWorldPosition();
};