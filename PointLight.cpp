#include "PointLight.h"

PointLight::PointLight(int index)
{
	this->lightIndex = index;
}

void PointLight::SetPosition(glm::vec3& pos)
{
	this->position = pos;
}

void PointLight::SetColor(glm::vec3& color)
{
	this->color = color;
}

void PointLight::SetAmbient(glm::vec3& ambient)
{
	this->ambient = ambient;
}

void PointLight::SetUniforms(Shader& shader)
{
	std::string prefix = "pointLight[" + std::to_string(lightIndex) + "].";
	shader.SetUniform3fv((prefix + "position").c_str(), this->position);
	shader.SetUniform3fv((prefix + "ambient").c_str(), glm::vec3(this->color.x * this->ambient.x, this->color.y * this->ambient.y, this->color.z * this->ambient.z));
	shader.SetUniform3fv((prefix + "diffuse").c_str(), this->color);
	shader.SetUniform3fv((prefix + "specular").c_str(), this->color);
	shader.SetUniformFloat((prefix + "constant").c_str(), this->constant);
	shader.SetUniformFloat((prefix + "linear").c_str(), this->linear);
	shader.SetUniformFloat((prefix + "quadratic").c_str(), this->quadratic);
}

void PointLight::Draw(Shader& shader, Renderer& renderer)
{
	renderer.Draw(position, *ContentManager::Textures["woodenFloor"], scale, glm::vec3(0), 0.f, color, shader);
}
