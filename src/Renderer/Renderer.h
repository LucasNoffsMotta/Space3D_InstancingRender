#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

#include "Shader.h"
#include "../OpenGL/VAO.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include "Model.h"
#include "Camera.h"





class Renderer
{
private:
	void InitCubeWithNormalsAndTextureRenderData();
	void InitViewAndProjectionMatrices();


	Shader shader;
	VAO vao;
	VAO aimDotVao;

public:
	int MAX_POINT_LIGHTS = 10;
	void Draw(glm::vec3 translation, Texture& texture, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 color, Shader& shader);
	void DrawInstances(int amount, Texture& texture, Texture& diffuseMap, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 color, Shader& shader);
	void DrawQuad2D(glm::vec3 scale, glm::vec3 color, Shader& shader, float screen_width, float screen_height);
	void SetInstancedTranslations(int amount);
	void SetCircularInstancesPositions(float radius, float offSet, int amount);
	Renderer();

	void SetModelMatrices(glm::vec3* translations, int ammount);
	void SetInstancesBuffers(int amount);
	void InitQuad2DRenderData();
	void InitQuad3DRenderData();

	glm::mat4 projection;
	glm::mat4 view;

	//Instancing:
	glm::mat4* modelMatrices;  //Large object array 
	glm::vec3* instancesTranslationPtr;   //Large object array 
};




#endif // !RENDERER_CLASS_H
