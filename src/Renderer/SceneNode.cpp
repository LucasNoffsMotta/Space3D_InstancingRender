#include "SceneNode.h"

void SceneNode::SetShaderMap(std::map<eRenderMode, Shader*> shaderMap)
{
	this->shaderMap = shaderMap;
}

void SceneNode::SetUpNodeLightsUniforms(Shader* shader)
{
	for (int i = 0; i < Lights.size(); i++)
	{
		Lights[i]->SetUniformsTest(*shader);
	}
}

void SceneNode::SetRenderModeOnMainShader(eRenderMode mode, Shader* mainShader)
{
	if (mode == eRenderMode::FullRender)
	{
		mainShader->SetUniformInt("LightsOn", 1);
		SetUpNodeLightsUniforms(mainShader);
	}

	else if (mode == eRenderMode::NoLights_NoTextures)
	{
		mainShader->SetUniformInt("DebugMode", 1);
	}

	else if (mode == eRenderMode::DepthTestMode)
	{
		mainShader->SetUniformInt("DepthTestMode", 1);
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
	if (level == eHierarchyLevel::SKY_BOX)
	{
		Shader* skyBoxShader = shaderMap[eRenderMode::SkyBox];
		RenderSkyBox(skyBoxShader);
	}
	if (level == eHierarchyLevel::TRANSLUCID)
	{
		Shader* mainShader = shaderMap[eRenderMode::FullRender];
		mainShader->Activate();
		SetRenderModeOnMainShader(ContentManager::GlobalRenderMode, mainShader);
		RenderTranslucidObjectsNoStenciltest(mainShader);
	}

	else if (level == eHierarchyLevel::NO_STENCIL_TEST)
	{
		Shader* mainShader = shaderMap[eRenderMode::FullRender];
		mainShader->Activate();
		SetRenderModeOnMainShader(ContentManager::GlobalRenderMode, mainShader);
		RenderRegularObjectsNoStencilTest(mainShader);
	}

	else if (level == eHierarchyLevel::STENCIL_TEST)
	{
		Shader* mainShader = shaderMap[eRenderMode::FullRender];
		Shader* stencilMaskShader = shaderMap[eRenderMode::Outline];
		mainShader->Activate();
		SetRenderModeOnMainShader(ContentManager::GlobalRenderMode, mainShader);
		RenderStencilTestOn(mainShader);
		RenderOutlineMask(stencilMaskShader);
	}

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
	modelMatrix = entity->RotateMatrix(modelMatrix);
	modelMatrix = glm::scale(modelMatrix, entity->GetScale() * scale);
	shader->SetUniformMatrix4fv("model", modelMatrix);
	entity->Draw(shader);
}


void SceneNode::RenderRegularObjectsNoStencilTest(Shader* shader)
{
	glStencilMask(0x00);

	for (int i = 0; i < Entities.size(); i++)
	{
		Entity* entity = Entities[i];

		if (entity->GetModel()->useInstanced)
		{
			Shader* shaderInstanced = shaderMap[eRenderMode::FullRender_Instanced];
			shaderInstanced->Activate();
			SetModelMatrixAndCallDraw(entity, shaderInstanced, glm::vec3(1));
		}

		else
		{
			shader->Activate();
			SetModelMatrixAndCallDraw(entity, shader, glm::vec3(1));
		}

		entity->Update(Controller);
	}
}

void SceneNode::RenderTranslucidObjectsNoStenciltest(Shader* shader)
{
	glStencilMask(0x00);

	std::map<float, Entity*> orderedEntities = GetOrderedTranslucidEntities();

	for (auto iter = orderedEntities.rbegin(); iter != orderedEntities.rend(); iter++)
	{
		Entity* entity = iter->second;

		if (entity->GetModel()->useInstanced)
		{
			Shader* shaderInstanced = shaderMap[eRenderMode::FullRender_Instanced];
			shaderInstanced->Activate();
			SetModelMatrixAndCallDraw(entity, shaderInstanced, glm::vec3(1));
		}

		else
		{
			shader->Activate();
			SetModelMatrixAndCallDraw(entity, shader, glm::vec3(1));
		}


		entity->Update(Controller);
	}
}


void SceneNode::RenderStencilTestOn(Shader* shader)
{
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);

	for (int i = 0; i < Entities.size(); i++)
	{
		Entity* entity = Entities[i];

		if (entity->GetModel()->useInstanced)
		{
			Shader* shaderInstanced = shaderMap[eRenderMode::FullRender_Instanced];
			shaderInstanced->Activate();
			SetModelMatrixAndCallDraw(entity, shaderInstanced, glm::vec3(1));
		}

		else
		{
			shader->Activate();
			SetModelMatrixAndCallDraw(entity, shader, glm::vec3(1));
		}

		entity->Update(Controller);
	}
}

void SceneNode::RenderSkyBox(Shader* shader)
{
	glDepthMask(GL_FALSE);
	shader->Activate();

	for (int i = 0; i < Entities.size(); i++)
	{
		Entity* entity = Entities[i];
		entity->Draw(shader);
	}

	glDepthMask(GL_TRUE);
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
		if (!entity->outline || entity->GetModel()->useInstanced) continue;
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

	Shader* mainShader = shaderMap[eRenderMode::FullRender];
	Shader* stencilMaskShader = shaderMap[eRenderMode::Outline];
	Shader* instanced = shaderMap[eRenderMode::FullRender_Instanced];
	Shader* skyBox = shaderMap[eRenderMode::SkyBox];

	mainShader->Activate();
	mainShader->SetUniformMatrix4fv("view", view);

	stencilMaskShader->Activate();
	stencilMaskShader->SetUniformMatrix4fv("view", view);

	instanced->Activate();
	instanced->SetUniformMatrix4fv("view", view);

	skyBox->Activate();
	skyBox->SetUniformMatrix4fv("view", glm::mat4(glm::mat3(view)));	
}

void SceneNode::SetProjectionMatrix(glm::mat4& projection)
{
	Shader* mainShader = shaderMap[eRenderMode::FullRender];
	Shader* stencilMaskShader = shaderMap[eRenderMode::Outline];

	mainShader->Activate();
	mainShader->SetUniformMatrix4fv("projection", projection);

	stencilMaskShader->Activate();
	stencilMaskShader->SetUniformMatrix4fv("projection", projection);
}

std::map<float, Entity*> SceneNode::GetOrderedTranslucidEntities()
{
	std::vector<Entity*> translucidGroup;
	Camera* cam = Cameras.back();
	std::map<float, Entity*> orderedMap;

	for (auto entity : Entities)
	{
		if (entity->GetIsTranslucid())
		{
			translucidGroup.push_back(entity);
		}
	}

	for (int i = 0; i < translucidGroup.size(); i++)
	{
		float distance = glm::length(cam->CameraPos - translucidGroup[i]->GetWorldPosition());
		orderedMap[distance] = translucidGroup[i];
	}

	return orderedMap;
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

