#include "Entity.h"


void Entity::SetWorldPosition(glm::vec3& newPos)
{
    this->worldPosition = newPos;
}

void Entity::SetScale(glm::vec3& newScale)
{
    this->scale = newScale;
}

glm::vec3 Entity::GetWorldPosition()
{
    return this->worldPosition;
}

glm::vec3 Entity::GetScale()
{
    return this->scale;
}

void Entity::Update(InputManager* controller)
{
    if (controller->Inputs[eInput::None] || attachedCamera == nullptr)
    {
        return;
    }

    if (controller->Inputs[eInput::Arrow_Up])
    {
        worldPosition.z -= 10 * TimeHelper::GetDeltaTime();
        attachedCamera->CameraPos.z -= 10 * TimeHelper::GetDeltaTime();
    }

    if (controller->Inputs[eInput::Arrow_Down])
    {
        worldPosition.z += 10 * TimeHelper::GetDeltaTime();
        attachedCamera->CameraPos.z += 10 * TimeHelper::GetDeltaTime();
    }

    if (controller->Inputs[eInput::Arrow_Left])
    {
        worldPosition.x -= 10 * TimeHelper::GetDeltaTime();
        attachedCamera->CameraPos.x -= 10 * TimeHelper::GetDeltaTime();
    }

    if (controller->Inputs[eInput::Arrow_Right])
    {
        worldPosition.x += 10 * TimeHelper::GetDeltaTime();
        attachedCamera->CameraPos.x += 10 * TimeHelper::GetDeltaTime();
    }
}

void Entity::SetRotationAngle(float angle)
{
    rotationAngle = angle;
}

void Entity::SetModel(Model* model)
{
    this->model = model;
}

Model* Entity::GetModel()
{
    return this->model;
}

int Entity::GetID()
{
    return ID;
}

void Entity::SetID(int lastID)
{
    ID = lastID++;
}

void Entity::Draw(Shader* shader)
{
    this->model->Draw(*shader);
}

Entity::Entity(Model* model, eHierarchyLevel level)
{
    this->model = model;
    this->HIERARCHY_LEVEL = level;
}

Entity::Entity()
{

}

void Entity::AttatchCamera(Camera* cam, float distance)
{
    attachedCamera = cam;
    cam->CameraPos = GetWorldPosition() + glm::vec3(0, distance, 10);
    glm::vec3 direction = GetWorldPosition() - cam->CameraPos;
    cam->CameraFront = glm::normalize(direction);
    cam->mode = eCameraMode::TopDown;
    outline = true;
}