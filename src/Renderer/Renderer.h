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
	void InitCubeRenderData();
	Shader shader;
	VAO vao;
	VAO aimDotVao;
	void CreatePointLights();
	void CreateSpotLights();
	void CreateDirectionalLights();
	void SetSceneLightUniforms(Shader& shader);

public:
	int MAX_POINT_LIGHTS = 10;
	void Draw(glm::vec3 translation, Texture& texture, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 color, Shader& shader);
	void DrawInstances(int amount, Texture& texture, Texture& diffuseMap, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 color, Shader& shader);
	void DrawQuad2D(glm::vec3 scale, glm::vec3 color, Shader& shader, float screen_width, float screen_height);
	void DrawScene(Shader& shader, Shader& stencilShader);
	void SetInstancedTranslations(int amount);
	Renderer();

	void SetModelMatrices(glm::vec3* translations, int ammount);
	void SetInstancesBuffers(int amount);
	void InitQuad2DRenderData();

	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4* modelMatrices;  //Large object array 
	glm::vec3* instancesTranslationPtr;   //Large object array 
};




#endif // !RENDERER_CLASS_H
