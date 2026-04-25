#include "Shader.h"
#include "VAO.h"
#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

class Renderer
{
public:
	void Draw(glm::vec3 translation, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 color, Shader& shader);
	Renderer();
	void SetActiveShader(Shader& shader);
	glm::mat4 projection;
	glm::mat4 view;

private:
	void InitRenderData();
	Shader shader;
	VAO vao;


};




#endif // !RENDERER_CLASS_H
#pragma once
