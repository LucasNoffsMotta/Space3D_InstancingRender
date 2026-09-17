#include "BaseLight.h"

BaseLight::BaseLight()
{
}

BaseLight::BaseLight(int index)
{
	this->lightIndex = index;
}

void BaseLight::SetPosition(glm::vec3& pos)
{
	this->position = pos;
}

void BaseLight::SetColor(glm::vec3& color)
{
	this->color = color;
}

void BaseLight::SetAmbient(glm::vec3& ambient)
{
	this->ambient = ambient;
}

std::string BaseLight::SetUniforms(Shader& shader, std::string shaderStruct)
{
	std::string prefix = shaderStruct + "[" + std::to_string(lightIndex) + "].";
	shader.SetUniform3fv((prefix + "ambient").c_str(), glm::vec3(this->color.x * this->ambient.x, this->color.y * this->ambient.y, this->color.z * this->ambient.z));
	shader.SetUniform3fv((prefix + "diffuse").c_str(), this->color);
	shader.SetUniform3fv((prefix + "specular").c_str(), this->color);
	return prefix;
}

void BaseLight::Draw(Shader& shader, Texture& texture, Renderer& renderer)
{
	renderer.Draw(position, texture, scale, glm::vec3(0), 0.f, color, shader);
}

