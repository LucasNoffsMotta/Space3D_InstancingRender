#include "PointLight.h"



PointLight::PointLight(int index)
{
	this->lightIndex = index;
}

void PointLight::SetPointLightUniforms(Shader& shader)
{
	std::string prefix = BaseLight::SetUniforms(shader, "pointLight");
	shader.SetUniform3fv((prefix + "position").c_str(), this->position);
	shader.SetUniformFloat((prefix + "constant").c_str(), this->constant);
	shader.SetUniformFloat((prefix + "linear").c_str(), this->linear);
	shader.SetUniformFloat((prefix + "quadratic").c_str(), this->quadratic);
}

void PointLight::DrawPointLight(Shader& shader, Texture& texture, Renderer& renderer)
{
	BaseLight::Draw(shader, texture, renderer);
}
