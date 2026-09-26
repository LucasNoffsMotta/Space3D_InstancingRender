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
	void InitRenderData();
	Shader shader;
	VAO vao;
	VAO aimDotVao;
	VAO bulletVao;
	void CreatePointLights();
	void CreateSpotLights();
	void CreateDirectionalLights();

public:
	int MAX_POINT_LIGHTS = 10;
	void Draw(glm::vec3 translation, Texture& texture, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 color, Shader& shader);
	void DrawInstances(int amount, Texture& texture, Texture& diffuseMap, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 color, Shader& shader);
	void DrawAimDot(glm::vec3 scale, glm::vec3 color, Shader& shader, float screen_width, float screen_height);
	void DrawBullet(glm::vec3 translation, glm::vec3 scale, glm::vec3 rotation, float rotationAngle, glm::vec3 color, Shader& shader);
	void DrawScene(Shader& shader);

	void DrawModel(Model& model, glm::vec3& translation, glm::vec3 scale, Shader& shader);


	void SetInstancedTranslations(int amount);
	Renderer();

	void SetActiveShader(Shader& shader);
	void SetModelMatrices(glm::vec3* translations, int ammount);
	void SetInstancesBuffers(int amount);

	glm::vec3 GetTranslationPos(int index);
	void InitAimDotRenderData();
	void InitBulletRenderData();

	bool bulletShoot = false;
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4* modelMatrices;  //Large object array 
	glm::vec3* instancesTranslationPtr;   //Large object array 
	glm::vec3 bulletDirection;
	glm::vec3 bulletPosition;
};




#endif // !RENDERER_CLASS_H
