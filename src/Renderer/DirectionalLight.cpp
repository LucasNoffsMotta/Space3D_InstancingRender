#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(int index, eLightType type)
{
	color = glm::vec3(1.f, 1.f, 0.3f);
	this->lightIndex = index;
	this->type = type;
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

void DirectionalLight::SetUniformsTest(Shader& shader)
{
	std::string prefix = BaseLight::SetUniforms(shader);
	shader.SetUniform3fv((prefix + "direction").c_str(), this->direction);
}

void DirectionalLight::DrawDirectionalLight(Shader& shader, Texture& texture, Renderer& renderer)
{
	BaseLight::Draw(shader, texture, renderer);
}

void DirectionalLight::SetUniforms(Shader& shader)
{
	std::string prefix = BaseLight::SetUniforms(shader);
	shader.SetUniform3fv((prefix + "direction").c_str(), this->direction);
}
