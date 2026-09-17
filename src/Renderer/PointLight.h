#pragma once
#include <glm/glm.hpp>
#include "Shader.h"
#include "Renderer.h"
#include "BaseLight.h"

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