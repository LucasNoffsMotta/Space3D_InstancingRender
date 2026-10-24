#pragma once
#include <glm/glm.hpp>
#include "../Helper/InputManager.h"
#include "Model.h"

enum eHierarchyLevel : int
{
	SKY_BOX,
	TRANSLUCID,
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
	//If rotate Yaw, the front vector should rotate as well
	//The Roll Axis should rotate around the front axis
	glm::vec3 Front = glm::vec3(0, 0, 1);
	glm::vec3 Up = glm::vec3(0, 1, 0);
	glm::vec3 PitchAxis = glm::vec3(0, 0, 1);
	glm::vec3 YawAxis = glm::vec3(0, 1, 0);
	glm::vec3 RollAxis = glm::vec3(1, 0, 0);

	int Index;
	eHierarchyLevel HIERARCHY_LEVEL = eHierarchyLevel::NO_STENCIL_TEST;

	//Spring Arm: Distance from the object, relative position from the object

	float cameraDistance;
	glm::vec3 cameraDirection;

	bool isTranslucid;

public:
	Camera* attachedCamera;
	glm::mat4 modelMatrix = glm::mat4(1);
	void SetIsTranslucid(bool isTranslucid);
	bool GetIsTranslucid();
	glm::vec3 rotationAxis = glm::vec3(0, 1, 0);
	bool outline = false;
	Entity(Model* model, eHierarchyLevel level);
	Entity();
	void AttatchCamera(Camera* cam, float distance);
	void Update(InputManager* controller);
	void SetModel(Model* model);
	Model* GetModel();
	glm::mat4 RotateMatrix(glm::mat4& modelMatrix);
	glm::vec3 GetDirection();

	void FixModelRotationOnLoad(glm::vec3 axis, float offeset);


	void SetWorldPosition(glm::vec3& newPos);
	void SetScale(glm::vec3& newScale);
	glm::vec3 GetWorldPosition();
	glm::vec3 GetScale();
	int GetID();
	void SetID(int lastID);
	void Draw(Shader* shader);

};