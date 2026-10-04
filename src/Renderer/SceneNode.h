#pragma once
#include <vector>
#include "BaseLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"

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
	std::map<eRenderMode, Shader*> shaderMap;
	InputManager* Controller;
	int nodeLevel;

	void UpdateController();
	void RenderOutlineMask(Shader* shader);
	void RenderRegularObjectsNoStencilTest(Shader* shader);
	void RenderWired(Shader* shader);
	void RenderStencilTestOn(Shader* shader);
	void SetViewMatrix();
	void SetUpNodeLights(Shader* shader);

public:
	std::vector<SceneNode*> children;
	void SetShaderMap(std::map<eRenderMode, Shader*> parentMap);
	Shader* QueryShader(eRenderMode mode);
	SceneNode(int nodeLevel);
	void AttatchCamera(Camera* camera);
	void AttatchLight(BaseLight* light);
	void AttatchModel(Model* model);
	void AttatchChildNode(SceneNode* child);
	void AttatchController(InputManager* controller);
	void Render();
	void SetProjectionMatrix(glm::mat4& projection);
	void UpdateNode();
};