#include "PointLight.h"


float& PointLight::GetConstant()
{
	return this->constant;
}

float& PointLight::GetLinear()
{
	return this->linear;
}

float& PointLight::GetQuadratic()
{
	return this->quadratic;
}

PointLight::PointLight(int index, eLightType type)
{
	this->lightIndex = index;
	this->type = type;
}

void PointLight::SetUniforms(Shader& shader)
{
	std::string prefix = BaseLight::SetBaseUniforms(shader);
	shader.SetUniform3fv((prefix + "position").c_str(), this->position);
	shader.SetUniformFloat((prefix + "constant").c_str(), this->constant);
	shader.SetUniformFloat((prefix + "linear").c_str(), this->linear);
	shader.SetUniformFloat((prefix + "quadratic").c_str(), this->quadratic);
}

eLightType PointLight::GetLightType()
{
	return this->type;
}
