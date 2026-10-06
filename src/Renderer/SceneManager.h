#pragma once
#include <map>
#include "SceneNode.h"


struct HierarchyLevel
{
	eHierarchyLevel level;
	int index;

	HierarchyLevel(eHierarchyLevel _level, int _index)
	{
		level = _level;
		index = _index;
	}
};

class SceneManager
{
private:
	std::map<eRenderMode, Shader*> RootShaderMap;
	std::vector<Model*> Models;
	std::vector<HierarchyLevel> hierarchy;
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
	void FillSceneTree(SceneNode* node);
	void SetUpSceneProjection(glm::mat4& projection);
	void LoadViewAndProjectionMatrices();
	void InitHierarchyStructs();
	void LoadEmptyTreeBasedOnLevels();
	void AddNode(SceneNode* node, int level);


public:
	void InitScene();	
	void RenderScene();
};