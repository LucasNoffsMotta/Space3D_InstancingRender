#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(int index)
{
	color = glm::vec3(0.5f, 0.01f, 0.01f);
	this->lightIndex = index;
}

void DirectionalLight::SetDirection(glm::vec3& dir)
{
	this->direction = dir;
}

void DirectionalLight::SetAmbient(glm::vec3& ambient)
{
	this->ambient = ambient;
}

void DirectionalLight::SetDiffuse(glm::vec3& diff)
{
	this->diffuse = diff;
}

void DirectionalLight::SetSpecular(glm::vec3& spec)
{
	this->specular = spec;
}

void DirectionalLight::DrawDirectionalLight(Shader& shader, Texture& texture, Renderer& renderer)
{
	BaseLight::Draw(shader, texture, renderer);
}

void DirectionalLight::SetDirectionalLightUniforms(Shader& shader)
{
	std::string prefix = BaseLight::SetUniforms(shader, "spotLight");
	shader.SetUniform3fv((prefix + "direction").c_str(), this->direction);
}
