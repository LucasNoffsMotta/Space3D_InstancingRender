#pragma once
#include <vector>
#include "BaseLight.h"

enum eRenderMode:uint8_t {
	Regular, //Lit, texture, etc
	StencilMask, //Mask shader
	WiredOn //Wire only shader
};

class SceneNode
{
private:
	//Models, lights, cameras
	//Shaders
	//Query singleton from shaders based on render mode
	//Shaders will be shared on the tree hierarquy -> 

	std::vector<BaseLight*> Lights;
	std::vector<Model*> Models;
	std::vector<Camera*> Cameras;
	std::vector<SceneNode*> children;
	std::map<eRenderMode, Shader*> shaderMap;
	int nodeLevel;
	Shader* currentShader;
	

public:
	void SetShaderMap(std::map<eRenderMode, Shader*> parentMap);
	void SetUpNodeLights(Shader* shader);
	Shader* QueryShader(eRenderMode mode);
	SceneNode(int nodeLevel);
	void AttatchCamera(Camera* camera);
	void AttatchLight(BaseLight* light);
	void AttatchModel(Model* model);
	void AttatchChildNode(SceneNode* child);
	void Render(eRenderMode mode, Shader* shader);
	void RenderStencilTestOn(Shader* shader);
	void RenderOutlineMask(Shader* shader);
	void RenderRegularObjectsNoStencilTest(Shader* shader);
	void RenderWired(Shader* shader);
};