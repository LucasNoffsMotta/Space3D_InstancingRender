#include "SpotLight.h"


SpotLight::SpotLight()
{
}

SpotLight::SpotLight(int index, eLightType type)
{
	this->lightIndex = index;
	this->type = type;
}


void SpotLight::SetDirection(glm::vec3& dir)
{
	this->direction = dir;
}


void SpotLight::SetUniforms(Shader& shader)
{
	std::string prefix = BaseLight::SetBaseUniforms(shader);
	shader.SetUniform3fv((prefix + "position").c_str(), this->position);
	shader.SetUniform3fv((prefix + "direction").c_str(), this->direction);
	shader.SetUniformFloat((prefix + "constant").c_str(), this->constant);
	shader.SetUniformFloat((prefix + "linear").c_str(), this->linear);
	shader.SetUniformFloat((prefix + "quadratic").c_str(), this->quadratic);

	shader.SetUniformFloat((prefix + "innerCutoff").c_str(), this->innerCutOff);
	shader.SetUniformFloat((prefix + "outerCutoff").c_str(), this->outerCutoff);
}

eLightType SpotLight::GetLightType()
{
	return this->type;
}

