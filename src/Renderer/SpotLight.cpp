#include "SpotLight.h"
#include "PointLight.h"


SpotLight::SpotLight(int index)
{
	this->lightIndex = index;
}

void SpotLight::SetSpotLightLightUniforms(Shader& shader)
{
	std::string prefix = BaseLight::SetUniforms(shader, "spotLight");
	shader.SetUniform3fv((prefix + "position").c_str(), this->position);
	shader.SetUniform3fv((prefix + "direction").c_str(), this->direction);
	shader.SetUniformFloat((prefix + "constant").c_str(), this->constant);
	shader.SetUniformFloat((prefix + "linear").c_str(), this->linear);
	shader.SetUniformFloat((prefix + "quadratic").c_str(), this->quadratic);

	shader.SetUniformFloat((prefix + "innerCutoff").c_str(), this->innerCutOff);
	shader.SetUniformFloat((prefix + "outerCutoff").c_str(), this->outerCutoff);
}

void SpotLight::SetDirection(glm::vec3& dir)
{
	this->direction = dir;
}

void SpotLight::DrawSpotLight(Shader& shader, Texture& texture, Renderer& renderer)
{
	BaseLight::Draw(shader, texture, renderer);
}

