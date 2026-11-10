#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

//#include "SceneNode.h"
#include "Shader.h"
#include "../OpenGL/VAO.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include "Model.h"
#include "Camera.h"
#include "stb_image_write.h"
#include "DirectionalLight.h"





/// <summary>
/// This class is responsible for managing the buffer creations and manage the OPEN GL states.
/// </summary>
class Renderer
{
private:
	Shader shader;
	VAO vao;
	unsigned int rbo;
	unsigned int fbo;

	unsigned int frameBufferVao;
	unsigned int uboMatrices; //Update the buffer data here and all the shader programs will be updated!
	unsigned int uboDirLight; //Update the buffer data here and all the shader programs will be updated!

	/// <summary>
	/// Dont forget to attatch it to the framebuffer.
	/// </summary>
	Texture* frameBufferTexture;


	Texture* enviromentMapTexture;

	std::vector<Model*> DisplayModels;
	glm::vec3 ModelDisplayPos = glm::vec3(-1.7,-0.7,0);
	glm::vec3 ModelDisplayScale = glm::vec3(0.1);
	glm::mat4 ModelDisplayView = glm::mat4(1);
	float ModelDisplayRotationOffset = 0.f;
	int currentDisplayedModelIndex = 0;
	


public:
	Renderer();

	//Test: Take screenshot
	bool screnShotTaken = false;

	void ScreenShot(const char* filePath, GLFWwindow* window);

	//Display rotating model
	void RenderDisplayModel(Shader* shader);
	void GetAllLoadedModels();
	//void GetInput(SceneNode* nodeToAttatch);
	void GetInput();

	//Uniform buffers
	void InitUniformBufferObjects();
	void SetShadersBindingPointToUseUniformBuffer();
	void FillUboMatricesProjection(glm::mat4 projection);
	void FillUboDirLight(DirectionalLight& light);
	void FillUboMatricesView(glm::mat4 view);

	//Framebuffer
	void InitFrameBuffer();
	void InitRenderBuffer(int frameBufferSizeX, int frameBufferSizeY);
	void BindFrameBuffer();
	void UnbindFramebuffer();
	void InitFrameBufferScreenQuad();
	void InitFramebufferTexture();
	void InitEnviromentMapTexture();
	void RenderFramebuffer(Shader& shader);
	Texture* GetFramebufferTexture();
	Texture* GetEnviromentMapTexture() { return enviromentMapTexture; };

	void AttatchTextureToFramebuffer();
	void AttatchEnviromentMapToFramebuffer();
};




#endif // !RENDERER_CLASS_H
