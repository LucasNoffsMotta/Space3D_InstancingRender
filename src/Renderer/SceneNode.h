#pragma once
#include <vector>
#include "BaseLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"
#include "Entity.h"

enum eRenderMode:uint8_t {
	Regular, //Lit, texture, etc
	RegularInstanced,
	StencilMask, //Mask shader
	WiredOn //Wire only shader
};

struct HierarchyLevel;

class SceneNode
{
private:
	std::vector<BaseLight*> Lights;
	std::vector<Entity*> Entities;
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
	eHierarchyLevel level;
	std::vector<SceneNode*> children;
	void SetShaderMap(std::map<eRenderMode, Shader*> parentMap);
	Shader* QueryShader(eRenderMode mode);
	SceneNode(eHierarchyLevel nodeLevel);
	void AttatchCamera(Camera* camera);
	void AttatchLight(BaseLight* light);
	void AttatchEntity(Entity* entity);
	void AttatchChildNode(SceneNode* child);
	void AttatchController(InputManager* controller);
	void RenderNode();
	void SetModelMatrixAndCallDraw(Entity* entity, Shader* shader, glm::vec3 scale);
	void SetProjectionMatrix(glm::mat4& projection);
	void UpdateNode();
};