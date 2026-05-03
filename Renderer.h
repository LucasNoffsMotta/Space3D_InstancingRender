#include "Shader.h"
#include "VAO.h"
#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

class Renderer
{
public:
	void Draw(glm::vec3 translation, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 color, Shader& shader);
	void DrawInstances(glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 color, Shader& shader);


	void DrawInstances(int amount, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 color, Shader& shader);


	void SetInstancedTranslations(int amount);
	Renderer();

	void SetActiveShader(Shader& shader);
	void SetModelMatrices(glm::vec3* translations, int ammount);
	void SetInstancesBuffers(int amount);

	glm::vec3 GetTranslationPos(int index);

	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4* modelMatrices;
	glm::vec3* instancesTranslationPtr;


private:
	void InitRenderData();
	Shader shader;
	VAO vao;


};




#endif // !RENDERER_CLASS_H
#pragma once
