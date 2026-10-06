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

void SceneNode::AttatchModel(Model* model)
{
	Models.push_back(model);
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

void SceneNode::Render()
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
	}

	else if (level == eHierarchyLevel::OUTLINE_MASK)
	{
		//Third: Render Outline Mask
		RenderOutlineMask(stencilMaskShader);
	}

	if (children.size() > 0) {
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->Render();
		}
	}
}


void SceneNode::RenderRegularObjectsNoStencilTest(Shader* shader)
{
	glStencilMask(0x00);
	shader->Activate();

	for (int i = 0; i < Models.size(); i++)
	{
		Model* model = Models[i];

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, model->GetWorldPosition());

		if (model->rotationAngle > 0)
		{
			modelMatrix = glm::rotate(modelMatrix, glm::radians(model->rotationAngle), model->rotationAxis);
		}

		modelMatrix = glm::scale(modelMatrix, model->GetScale());
		shader->SetUniformMatrix4fv("model", modelMatrix);
		model->Draw(*shader);
	}
}


void SceneNode::RenderStencilTestOn(Shader* shader)
{
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);

	for (int i = 0; i < Models.size(); i++)
	{
		Model* model = Models[i];

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, model->GetWorldPosition());

		if (model->rotationAngle > 0)
		{
			modelMatrix = glm::rotate(modelMatrix, glm::radians(model->rotationAngle), model->rotationAxis);
		}

		modelMatrix = glm::scale(modelMatrix, model->GetScale());
		shader->SetUniformMatrix4fv("model", modelMatrix);
		model->Draw(*shader);
	}
}

void SceneNode::RenderOutlineMask(Shader* shader)
{
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDisable(GL_DEPTH_TEST);

	shader->Activate();
	for (int i = 0; i < Models.size(); i++)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		Model* model = Models[i];

		if (!model->outline) continue;

		modelMatrix = glm::translate(modelMatrix, model->GetWorldPosition());

		if (model->rotationAngle > 0)
		{
			modelMatrix = glm::rotate(modelMatrix, glm::radians(model->rotationAngle), model->rotationAxis);
		}

		modelMatrix = glm::scale(modelMatrix, model->GetScale() * glm::vec3(1.01));
		shader->SetUniformMatrix4fv("model", modelMatrix);
		model->Draw(*shader);
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
	Render();
}

