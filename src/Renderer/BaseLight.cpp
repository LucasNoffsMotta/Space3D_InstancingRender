#include "BaseLight.h"

BaseLight::BaseLight()
{
}

glm::vec3 BaseLight::GetWorldPosition()
{
	return this->position;
}

BaseLight::BaseLight(int index, eLightType type)
{
	this->lightIndex = index;
	this->type = type;
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

glm::vec3& BaseLight::GetColor()
{
	return this->color;
}

glm::vec3& BaseLight::GetAmbient()
{
	return ambient;
}

glm::vec3& BaseLight::GetDiffuse()
{
	return diffuse;
}

glm::vec3& BaseLight::GetSpecular()
{
	return specular;
}

void BaseLight::SetDirection(glm::vec3 dir)
{
}

std::string BaseLight::SetBaseUniforms(Shader& shader)
{
	std::string prefix = GetLightStrucUniformName() + "[" + std::to_string(lightIndex) + "].";
	shader.SetUniform3fv((prefix + "ambient").c_str(), glm::vec3(this->color.x * this->ambient.x, this->color.y * this->ambient.y, this->color.z * this->ambient.z));
	shader.SetUniform3fv((prefix + "diffuse").c_str(), glm::vec3(this->color.x * this->diffuse.x, this->color.y * this->diffuse.y, this->color.z * this->diffuse.z));
	shader.SetUniform3fv((prefix + "specular").c_str(), glm::vec3(this->color.x * this->specular.x, this->color.y * this->specular.y, this->color.z * this->specular.z));
	return prefix;
}

void BaseLight::SetUniforms(Shader& shader)
{
}

std::string BaseLight::GetLightStrucUniformName()
{
	switch (type) {
	case eLightType::Directional:
		return "dirLight";
	case eLightType::Point:
		return "pointLight";
	case eLightType::Spot:
		return "spotLight";
	default:
		return "";
	}
}

eLightType BaseLight::GetLightType()
{
	return eLightType();
}

