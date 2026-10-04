#pragma once

#include "BaseLight.h"
#include <glm/glm.hpp>


class PointLight : public BaseLight
{
private:
	float constant = 1;
	float linear = 0.09;
	float quadratic = 0.032;

public:
	PointLight(int index, eLightType type);
	void SetUniforms(Shader& shader);
	void DrawPointLight(Shader& shader, Texture& texture, Renderer& renderer);
	void SetUniformsTest(Shader& shader) override;
};