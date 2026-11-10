#pragma once
#include <vector>
#include "BaseLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"
#include "Entity.h"
#include "../Helper/eRenderMode.h"
#include "../Helper/ContentManager.h"

//struct HierarchyLevel;

class SceneNode
{
private:
	std::vector<BaseLight*> Lights;
	std::vector<Entity*> Entities;
	std::map<eRenderMode, Shader*> shaderMap;
	InputManager* Controller;
	int nodeLevel;
	std::map<float, Entity*> GetOrderedTranslucidEntities();


	void UpdateController();
	void RenderOutlineMask(Shader* shader);
	void RenderRegularObjectsNoStencilTest(Shader* shader);
	void RenderTranslucidObjectsNoStenciltest(Shader* shader);
	void RenderWired(Shader* shader);
	void RenderStencilTestOn(Shader* shader);
	void RenderSkyBox(Shader* shader);
	void SetViewMatrix(bool updateCamera, bool enviromentMap, glm::mat4 view);
	void SetUpNodeLightsUniforms(Shader* shader);
	void SetRenderModeOnMainShader(eRenderMode mode, Shader* mainShader);

public:
	eHierarchyLevel level;
	std::vector<SceneNode*> children;
	void SetShaderMap(std::map<eRenderMode, Shader*> parentMap);
	Shader* QueryShader(eRenderMode mode);

	SceneNode(eHierarchyLevel nodeLevel);
	void AttatchLight(BaseLight* light);
	void AttatchEntity(Entity* entity);
	void AttatchChildNode(SceneNode* child);
	void AttatchController(InputManager* controller);
	void RenderNode();
	void SetModelMatrixAndCallDraw(Entity* entity, Shader* shader, glm::vec3 scale);
	void SetProjectionMatrix(glm::mat4& projection);
	void UpdateNode(bool updateCamera, bool enviromentMap, glm::mat4 view=glm::mat4(1));
};