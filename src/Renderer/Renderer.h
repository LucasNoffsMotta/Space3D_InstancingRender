#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

#include "Shader.h"
#include "../OpenGL/VAO.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include "Model.h"
#include "Camera.h"
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
	Texture frameBufferTexture;

public:
	Renderer();

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
	void RenderFramebuffer(Shader& shader);
	Texture& GetFramebufferTexture();
};




#endif // !RENDERER_CLASS_H
