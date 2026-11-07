#pragma once
#include <map>
#include "SceneNode.h"
#include "Renderer.h"
#include "Entity.h"
#include "../Helper/eRenderMode.h"


struct HierarchyLevel
{
	eHierarchyLevel level;

	HierarchyLevel(eHierarchyLevel _level)
	{
		level = _level;
	}
};

class SceneManager
{
private:
	std::map<eRenderMode, Shader*> RootShaderMap;
	std::vector<Entity*> Entities;
	std::vector<HierarchyLevel> hierarchy;
	SceneNode* RootNode;

	glm::vec3 sceneOrigin = glm::vec3(0.f);
	glm::vec3 baseScale = glm::vec3(1);
	glm::mat4 Projection;
	std::vector<BaseLight*> GlobalLights;
	
	//FBO Test
	Entity* FboTestCube;

	//ROTATION TEST
	Entity* ControlledEntity;

	void InitFramebuffer();
	void SetGlobalLightUniforms(Shader& shader);
	void LoadShaderSingletons();
	void LoadModelsAndSetPositions();
	void LoadGlobalLigths();
	void LoadCamera();
	void FillSceneTree(SceneNode* node);
	void LoadProjectionMatrix();
	void InitHierarchyStructs();
	void LoadEmptyTreeBasedOnLevels();
	void AddNode(SceneNode* node, int level);



public:
	void InitScene();	
	void RenderScene(Window& window);
};