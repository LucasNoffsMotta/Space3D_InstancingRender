#pragma once

#include "BaseLight.h"

class SpotLight : public BaseLight
{
private:

	float constant = 1;
	float linear = 0.014;
	float quadratic = 0.0007;
	float innerCutOff = glm::cos(glm::radians(9.5f));
	float outerCutoff = glm::cos(glm::radians(25.0f));
	glm::vec3 direction = glm::vec3(1);

public:
	SpotLight(int index);
	void SetSpotLightLightUniforms(Shader& shader);
	void SetDirection(glm::vec3& dir);
	void DrawSpotLight(Shader& shader, Texture& texture, Renderer& renderer);
};

