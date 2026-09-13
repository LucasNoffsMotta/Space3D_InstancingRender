

#include "Render/Shader.h"
#include "Render/VAO.h"
#include <Game/Camera.h>
#include "../Texture.h"
#include <glm/glm.hpp>

#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H



class Renderer
{
private:
	void InitRenderData();
	Shader shader;
	VAO vao;
	VAO aimDotVao;
	VAO bulletVao;
	int MAX_POINT_LIGHTS = 100;
	void CreatePointLights();

public:
	void Draw(glm::vec3 translation, Texture& texture, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 color, Shader& shader);
	void DrawInstances(int amount, Texture& texture, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 color, Shader& shader);
	void DrawAimDot(glm::vec3 scale, glm::vec3 color, Shader& shader, float screen_width, float screen_height);
	void DrawBullet(glm::vec3 translation, glm::vec3 scale, glm::vec3 rotation, float rotationAngle, glm::vec3 color, Shader& shader);


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
	glm::mat4* modelMatrices;
	glm::vec3* instancesTranslationPtr;
	glm::vec3 bulletDirection;
	glm::vec3 bulletPosition;
};




#endif // !RENDERER_CLASS_H
