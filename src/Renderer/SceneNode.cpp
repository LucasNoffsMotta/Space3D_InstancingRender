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
		mainShader->SetUniformInt("rm.Full_LightsAndReflection", 1);
		mainShader->SetUniformInt("rm.DebugMode", 0);
		mainShader->SetUniformInt("rm.DepthTestMode", 0);
		mainShader->SetUniformInt("rm.LightsOff", 0);
		SetUpNodeLightsUniforms(mainShader);
	}

	else if (mode == eRenderMode::DebugMode)
	{
		mainShader->SetUniformInt("rm.Full_LightsAndReflection", 0);
		mainShader->SetUniformInt("rm.DebugMode", 1);
		mainShader->SetUniformInt("rm.DepthTestMode", 0);
		mainShader->SetUniformInt("rm.LightsOff", 0);
	}

	else if (mode == eRenderMode::DepthTestMode)
	{
		mainShader->SetUniformInt("rm.Full_LightsAndReflection", 0);
		mainShader->SetUniformInt("rm.DebugMode", 0);
		mainShader->SetUniformInt("rm.DepthTestMode", 1);
		mainShader->SetUniformInt("rm.LightsOff", 0);
	}

	else if (mode == eRenderMode::NoLights)
	{
		mainShader->SetUniformInt("rm.Full_LightsAndReflection", 0);
		mainShader->SetUniformInt("rm.DebugMode", 0);
		mainShader->SetUniformInt("rm.DepthTestMode", 0);
		mainShader->SetUniformInt("rm.LightsOff", 1);
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
		//TODO: Passing all lights to this shader, should pass only the Dir Light uniform
		//TODO: Should increase the ambient light on the skybox, it will always be darker than the scene objects
		Shader* skyBoxShader = shaderMap[eRenderMode::SkyBox];
		skyBoxShader->Activate();
		SetUpNodeLightsUniforms(skyBoxShader); 
		RenderSkyBox(skyBoxShader);

	}

	if (level == eHierarchyLevel::TRANSLUCID)
	{
		Shader* mainShader = shaderMap[eRenderMode::FullRender];
		mainShader->Activate();
		SetRenderModeOnMainShader(ContentManager::GlobalRenderMode, mainShader);
		RenderTranslucidObjectsNoStenciltest(mainShader);
	}

	if (level == eHierarchyLevel::NO_STENCIL_TEST)
	{
		Shader* mainShader = shaderMap[eRenderMode::FullRender];
		mainShader->Activate();
		SetRenderModeOnMainShader(ContentManager::GlobalRenderMode, mainShader);
		RenderRegularObjectsNoStencilTest(mainShader);
	}

	if (level == eHierarchyLevel::STENCIL_TEST)
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
	glDepthFunc(GL_LEQUAL);


	for (int i = 0; i < Entities.size(); i++)
	{
		Entity* entity = Entities[i];
		entity->Draw(shader);
	}

	glDepthFunc(GL_LESS);
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

void SceneNode::SetViewMatrix(bool updateCamera)
{
	glm::mat4 view = glm::mat4(1);
	if (updateCamera) 	view = ContentManager::Cameras["main"]->Update(ContentManager::Controllers["main"]);

	else
	{
		ContentManager::Cameras["second"]->CameraPos.x = ContentManager::Cameras["main"]->CameraPos.x;
		ContentManager::Cameras["second"]->CameraPos.z = ContentManager::Cameras["main"]->CameraPos.z;

		ContentManager::Cameras["second"]->CameraPos.x = ContentManager::Cameras["main"]->CameraPos.x;
		ContentManager::Cameras["second"]->CameraPos.z = ContentManager::Cameras["main"]->CameraPos.z;

		view = ContentManager::Cameras["second"]->CalculateView();
	}

	
	ContentManager::GlobalRenderer->FillUboMatricesView(view);
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
		float distance = glm::length(ContentManager::Cameras["main"]->CameraPos - translucidGroup[i]->GetWorldPosition());
		orderedMap[distance] = translucidGroup[i];
	}

	return orderedMap;
}

void SceneNode::UpdateController()
{
	Controller->GetMouseScreenPos();
	Controller->GetInput();
}

void SceneNode::UpdateNode(bool updateCamera)
{
	SetViewMatrix(updateCamera);
	RenderNode();
}

