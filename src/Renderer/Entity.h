#pragma once
#include <glm/glm.hpp>
#include "Model.h"

enum eHierarchyLevel : int
{
	NO_STENCIL_TEST,
	STENCIL_TEST,
	OUTLINE_MASK
};


class Entity
{
private:
	int ID;
	Model* model;
	glm::vec3 worldPosition;
	glm::vec3 scale;
	glm::vec3 rotation;
	int Index;
	eHierarchyLevel HIERARCHY_LEVEL = eHierarchyLevel::NO_STENCIL_TEST;

	//Spring Arm: Distance from the object, relative position from the object
	Camera* attachedCamera;
	float cameraDistance;
	glm::vec3 cameraDirection;






public:
	float rotationAngle = 0;
	glm::vec3 rotationAxis = glm::vec3(0, 1, 0);
	bool outline = false;
	Entity(Model* model, eHierarchyLevel level);
	Entity();
	void AttatchCamera(Camera* cam, float distance);
	void Update(InputManager* controller);
	void SetRotationAngle(float angle);
	void SetModel(Model* model);
	Model* GetModel();

	void SetWorldPosition(glm::vec3& newPos);
	void SetScale(glm::vec3& newScale);
	glm::vec3 GetWorldPosition();
	glm::vec3 GetScale();
	int GetID();
	void SetID(int lastID);
	void Draw(Shader* shader);

};