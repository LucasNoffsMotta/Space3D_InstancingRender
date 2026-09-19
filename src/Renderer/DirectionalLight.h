#pragma once

#include "BaseLight.h"


class DirectionalLight : BaseLight
{
private:
	glm::vec3 direction = glm::vec3(1);


public:
	DirectionalLight(int index);
	void SetDirection(glm::vec3& dir);
	void DrawDirectionalLight(Shader& shader, Texture& texture, Renderer& renderer);
	void SetDirectionalLightUniforms(Shader& shader);
	void SetAmbient(glm::vec3& ambient);
	void SetDiffuse(glm::vec3& diff);
	void SetSpecular(glm::vec3& spec);
};