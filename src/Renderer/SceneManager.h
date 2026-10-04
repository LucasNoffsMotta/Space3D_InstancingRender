#pragma once
#include <map>
#include "SceneNode.h"


class SceneManager
{
private:
	std::map<eRenderMode, Shader*> RootShaderMap;
	std::vector<Model*> Models;
	SceneNode* RootNode;
	glm::vec3 sceneOrigin = glm::vec3(0.f);
	glm::vec3 baseScale = glm::vec3(1);
	glm::mat4 Projection;
	glm::mat4 View;
	Camera* BaseCamera;
	std::vector<BaseLight*> GlobalLights;

	void LoadShaderSingletons();
	void LoadModelsAndSetPositions();
	void LoadGlobalLigths();
	void LoadCamera();
	void LoadSceneTree(int levels);
	void AddNode(SceneNode* parent, int level, int totalLevels);
	void SetUpSceneNode(SceneNode* node);
	void SetUpSceneProjection(glm::mat4& projection);
	void LoadViewAndProjectionMatrices();


public:
	void InitScene();	
	void RenderScene();
};