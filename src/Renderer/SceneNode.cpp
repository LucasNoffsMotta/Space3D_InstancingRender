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
		BaseLight* light = Lights[i];
		//light->SetUniforms()  Might need to create a abstract class
	}

}

Shader* SceneNode::QueryShader(eRenderMode mode)
{
	return nullptr;
}

SceneNode::SceneNode(int nodeLevel)
{
	this->nodeLevel = nodeLevel;
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

void SceneNode::Render(eRenderMode mode, Shader* shader)
{
	//First: Query the necessary shaders
	Shader* mainShader = shaderMap[eRenderMode::Regular];
	Shader* stencilMaskShader = shaderMap[eRenderMode::StencilMask];
	Shader* wireShader = shaderMap[eRenderMode::WiredOn];

	//Setup Lights
	SetUpNodeLights(mainShader);

	//First: Render Regular Objects
	RenderRegularObjectsNoStencilTest(mainShader);
	
	//Second: Render Stencil Test On
	RenderStencilTestOn(mainShader);

	//Third: Render Outline Mask
	RenderOutlineMask(stencilMaskShader);
}

void SceneNode::RenderStencilTestOn(Shader* shader)
{
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);

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
	}

	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glEnable(GL_DEPTH_TEST);
}

void SceneNode::RenderRegularObjectsNoStencilTest(Shader* shader)
{
	glStencilMask(0x00);
	shader->Activate();

	for (int i = 0; i < Models.size(); i++)
	{
		Model* model = Models[i];
		if (model->doStencilTest) continue;

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, model->GetWorldPosition());

		if (model->rotationAngle > 0)
		{
			modelMatrix = glm::rotate(modelMatrix, glm::radians(model->rotationAngle), model->rotationAxis);
		}

		modelMatrix = glm::scale(modelMatrix, model->GetScale());
		shader->SetUniformMatrix4fv("model", modelMatrix);
	}
}

void SceneNode::RenderWired(Shader* shader)
{
	//
}

