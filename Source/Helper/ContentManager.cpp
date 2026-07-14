#include "Helper/ContentManager.h"
#include <Render/Shader.h>

std::map<std::string, Shader>       ContentManager::Shaders;
std::map<std::string, glm::vec3>       ContentManager::Colors;

Shader ContentManager::LoadShader(const char* vertexSource, const char* fragmentSource, std::string shaderName)
{
    Shaders[shaderName] = Shader(vertexSource, fragmentSource);
    return Shaders[shaderName];
}

glm::vec3 ContentManager::GetColor(std::string color)
{
    return Colors[color];
}

void ContentManager::InsertColor(std::string name, glm::vec3 rgb)
{
    glm::vec3 normalizedColor = glm::vec3(rgb.x / 255.f, rgb.y / 255.f, rgb.z / 255.f);
    Colors[name] = normalizedColor;
}

Shader ContentManager::GetShader(std::string shader)
{
    return Shaders[shader];
}

void ContentManager::InitColors()
{
    glm::vec3 red = glm::vec3(255.f, 0.f, 0.f);
    glm::vec3 blue = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 green = glm::vec3(0.f, 255.f, 0.f);
    glm::vec3 yellow = glm::vec3(0.f, 255.f, 255.f);
    glm::vec3 brown = glm::vec3(150.f, 75.f, 0.f);
    glm::vec3 white = glm::vec3(255.f, 255.f, 255.f);
    InsertColor("red", red);
    InsertColor("blue", blue);
    InsertColor("green", green);
    InsertColor("yellow", yellow);
    InsertColor("brown", brown);
}
