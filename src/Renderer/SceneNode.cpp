#include "SceneNode.h"

void SceneNode::SetShaderMap(std::map<eRenderMode, Shader*> shaderMap)
{
	this->shaderMap = shaderMap;
}

void SceneNode::SetUpNodeLights(Shader* shader)
{
	shader->Activate();

	for (int i = 0; i < Lights.size(); i++)
	{
		Lights[i]->SetUniformsTest(*shader);
	}
}

Shader* SceneNode::QueryShader(eRenderMode mode)
{
	return nullptr;
}

SceneNode::SceneNode(eHierarchyLevel nodeLevel)
{
	this->level = nodeLevel;
}

void SceneNode::AttatchCamera(Camera* camera)
{
	Cameras.push_back(camera);
}

void SceneNode::AttatchLight(BaseLight* light)
{
	Lights.push_back(light);
}

void SceneNode::AttatchEntity(Entity * entity)
{
	Entities.push_back(entity);
}

void SceneNode::AttatchChildNode(SceneNode* child)
{
	children.push_back(child);
}

void SceneNode::AttatchController(InputManager* controller)
{
	if (this->Controller == nullptr)
	{
		this->Controller = controller;
	}
}

void SceneNode::RenderNode()
{
	//First: Query the necessary shaders
	Shader* mainShader = shaderMap[eRenderMode::Regular];
	Shader* stencilMaskShader = shaderMap[eRenderMode::StencilMask];
	Shader* wireShader = shaderMap[eRenderMode::WiredOn];

	//Setup Lights
	SetUpNodeLights(mainShader);

	if (level == eHierarchyLevel::NO_STENCIL_TEST)
	{
		//First: Render Regular Objects
		RenderRegularObjectsNoStencilTest(mainShader);
	}

	else if (level == eHierarchyLevel::STENCIL_TEST)
	{
		//Second: Render Stencil Test On
		RenderStencilTestOn(mainShader);
		RenderOutlineMask(stencilMaskShader);
	}

	//else if (level == eHierarchyLevel::OUTLINE_MASK)
	//{
	//	//Third: Render Outline Mask
	//	RenderOutlineMask(stencilMaskShader);
	//}

	if (children.size() > 0) {
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->RenderNode();
		}
	}
}

void SceneNode::SetModelMatrixAndCallDraw(Entity* entity, Shader* shader, glm::vec3 scale)
{
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, entity->GetWorldPosition());

	if (entity->rotationAngle > 0)
	{
		modelMatrix = glm::rotate(modelMatrix, glm::radians(entity->rotationAngle), entity->rotationAxis);
	}

	modelMatrix = glm::scale(modelMatrix, entity->GetScale() * scale);
	shader->SetUniformMatrix4fv("model", modelMatrix);
	entity->Draw(shader);
}


void SceneNode::RenderRegularObjectsNoStencilTest(Shader* shader)
{
	glStencilMask(0x00);
	shader->Activate();

	for (int i = 0; i < Entities.size(); i++)
	{
		Entity* entity = Entities[i];
		SetModelMatrixAndCallDraw(entity, shader, glm::vec3(1));
	}
}


void SceneNode::RenderStencilTestOn(Shader* shader)
{
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);

	for (int i = 0; i < Entities.size(); i++)
	{
		Entity* entity = Entities[i];
		SetModelMatrixAndCallDraw(entity, shader, glm::vec3(1));
	}
}

void SceneNode::RenderOutlineMask(Shader* shader)
{
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDisable(GL_DEPTH_TEST);

	shader->Activate();
	for (int i = 0; i < Entities.size(); i++)
	{
		Entity* entity = Entities[i];
		if (!entity->outline) continue;
		SetModelMatrixAndCallDraw(entity, shader, glm::vec3(1.01));
	}

	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glEnable(GL_DEPTH_TEST);
}

void SceneNode::RenderWired(Shader* shader)
{
	//
}

void SceneNode::SetViewMatrix()
{
	glm::mat4 view = Cameras.back()->Update(Controller);
	Shader* mainShader = shaderMap[eRenderMode::Regular];
	Shader* stencilMaskShader = shaderMap[eRenderMode::StencilMask];
	Shader* wireShader = shaderMap[eRenderMode::WiredOn];

	mainShader->Activate();
	mainShader->SetUniformMatrix4fv("view", view);

	stencilMaskShader->Activate();
	stencilMaskShader->SetUniformMatrix4fv("view", view);

	wireShader->Activate();
	wireShader->SetUniformMatrix4fv("view", view);
}

void SceneNode::SetProjectionMatrix(glm::mat4& projection)
{
	Shader* mainShader = shaderMap[eRenderMode::Regular];
	Shader* stencilMaskShader = shaderMap[eRenderMode::StencilMask];
	Shader* wireShader = shaderMap[eRenderMode::WiredOn];

	mainShader->Activate();
	mainShader->SetUniformMatrix4fv("projection", projection);

	stencilMaskShader->Activate();
	stencilMaskShader->SetUniformMatrix4fv("projection", projection);

	wireShader->Activate();
	wireShader->SetUniformMatrix4fv("projection", projection);
}

void SceneNode::UpdateController()
{
	Controller->GetMouseScreenPos();
	Controller->GetInput();
}

void SceneNode::UpdateNode()
{
	UpdateController();
	SetViewMatrix();
	RenderNode();
}

