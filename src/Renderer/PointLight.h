#pragma once

#include "BaseLight.h"
#include <glm/glm.hpp>


class PointLight : public BaseLight
{
private:
	float constant = 1;
	float linear = 0.014;
	float quadratic = 0.0007;

public:
	PointLight(int index);
	void SetPointLightUniforms(Shader& shader);
	void DrawPointLight(Shader& shader, Texture& texture, Renderer& renderer);
};