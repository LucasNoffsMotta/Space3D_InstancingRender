#include "DirectionalLight.h"
#include "Entity.h"

DirectionalLight::DirectionalLight(int index, eLightType type)
{
	color = glm::vec3(0.0f, 0.f, 0.01f);
	this->lightIndex = index;
	this->type = type;
}

void DirectionalLight::SetDirection(glm::vec3& dir)
{
	this->direction = dir;
}

void DirectionalLight::SetAmbient(glm::vec3& ambient)
{
	this->ambient = ambient;
}

void DirectionalLight::SetDiffuse(glm::vec3& diff)
{
	this->diffuse = diff;
}

void DirectionalLight::SetSpecular(glm::vec3& spec)
{
	this->specular = spec;
}

glm::vec3 DirectionalLight::GetDirection()
{
	return direction;
}

void Entity::SetDisplayNormalsMode(bool displayNormals)
{
	this->displayNormals = displayNormals;
}

eLightType DirectionalLight::GetLightType()
{
	return this->type;
}

void DirectionalLight::SetUniforms(Shader& shader) 
{
	std::string prefix = BaseLight::SetBaseUniforms(shader);
	shader.SetUniform3fv((prefix + "direction").c_str(), this->direction);
}
