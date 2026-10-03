#pragma once
#include <map>
#include "SceneNode.h"


class SceneManager
{
private:
	std::map<eRenderMode, Shader*> RootShaderMap;
	std::vector<Model*> Models;
	SceneNode* RootNode;


public:
	void LoadShaderSingletons();
	void LoadModelsAndSetPositions();
	void LoadGlobalLigths();
	void LoadSceneTree();
	void SetUpSceneNode(SceneNode* node);
	void SetUpSceneProjection(glm::mat4& projection);
	void RenderScene();
};