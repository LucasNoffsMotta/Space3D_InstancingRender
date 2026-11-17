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

glm::vec3& BaseLight::GetAmbientColor()
{
	glm::vec3 colorAmbient = glm::vec3(this->color.x * this->ambient.x, this->color.y * this->ambient.y, this->color.z * this->ambient.z);
	return colorAmbient;
}

glm::vec3& BaseLight::GetDiffuse()
{
	return diffuse;
}

glm::vec3& BaseLight::GetSpecular()
{
	return specular;
}

glm::vec4& BaseLight::GetVec4Direction()
{
	glm::vec4 vec4Dir = glm::vec4(this->direction.x, this->direction.y, this->direction.z, 1);
	return vec4Dir;
}

glm::vec4& BaseLight::GetVec4Ambient()
{
	glm::vec3 colorAmbient = glm::vec3(this->color.x * this->ambient.x, this->color.y * this->ambient.y, this->color.z * this->ambient.z);
	glm::vec4 amb = glm::vec4(colorAmbient, 1);
	return amb;
}

glm::vec4& BaseLight::GetVec4AmbientColor()
{
	glm::vec4 vec4Color = glm::vec4(color.x, color.y, color.z, 1);
	return vec4Color;
}

glm::vec4& BaseLight::GetVec4Diffuse()
{
	glm::vec4 vec4Diff = glm::vec4(diffuse.x, diffuse.y, diffuse.z, 1);
	return vec4Diff;
}

glm::vec4& BaseLight::GetVec4Specular()
{
	glm::vec4 vec4Spec = glm::vec4(specular.x, specular.y, specular.z, 1);
	return vec4Spec;
}

void BaseLight::SetDirection(glm::vec3 dir)
{
}

glm::vec3& BaseLight::GetDirection()
{
	return direction;
}

std::string BaseLight::SetBaseUniforms(Shader& shader)
{
	std::string prefix = GetLightStrucUniformName() + "[" + std::to_string(lightIndex) + "].";
	shader.SetUniform3fv((prefix + "ambient").c_str(), glm::vec3(this->color.x * this->ambient.x, this->color.y * this->ambient.y, this->color.z * this->ambient.z));
	shader.SetUniform3fv((prefix + "diffuse").c_str(), glm::vec3(this->diffuse.x, this->diffuse.y, this->diffuse.z));
	shader.SetUniform3fv((prefix + "specular").c_str(), glm::vec3(this->specular.x, this->specular.y, this->specular.z));
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

