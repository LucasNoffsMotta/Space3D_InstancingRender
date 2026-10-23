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

    if (controller->Inputs[eInput::RotatePitch])
    {
        this->model->RotatePitch(1);
    }

    if (controller->Inputs[eInput::RotateYaw])
    {
        this->model->RotateYaw(1);
    }

    if (controller->Inputs[eInput::RotateRoll])
    {
        this->model->RotateRoll(1);
    }

    if (controller->Inputs[eInput::Arrow_Up])
    {
        worldPosition += (Front * 10.f) * TimeHelper::GetDeltaTime();
        attachedCamera->CameraPos += (Front * 10.f) * TimeHelper::GetDeltaTime();
    }

    if (controller->Inputs[eInput::Arrow_Down])
    {
        worldPosition -= (Front * 10.f) * TimeHelper::GetDeltaTime();
        attachedCamera->CameraPos -= (Front * 10.f) * TimeHelper::GetDeltaTime();
    }

    if (controller->Inputs[eInput::Arrow_Left])
    {
        this->model->RotateYaw((100 * TimeHelper::GetDeltaTime()) * -1.f);
    }

    if (controller->Inputs[eInput::Arrow_Right])
    {
        this->model->RotateYaw(100 * TimeHelper::GetDeltaTime());
    }
}


void Entity::SetModel(Model* model)
{
    this->model = model;
}

Model* Entity::GetModel()
{
    return this->model;
}

glm::mat4 Entity::RotateMatrix(glm::mat4& modelMatrix)
{
    float pitch = glm::radians(this->model->Pitch);
    float yaw = glm::radians(this->model->Yaw) - glm::radians(90.f); //Apply offset to model rotation
    float roll = glm::radians(this->model->Roll);

    Front.x = cos(yaw * cos(pitch));
    Front.y = sin(pitch);
    Front.z = sin(yaw * cos(pitch));
    Front = glm::normalize(Front);

    std::cout << "//Front x: " << Front.x << "// Front y: " << Front.y << "// Front z:  " << Front.z << std::endl;

    modelMatrix = glm::rotate(modelMatrix, yaw, -YawAxis);
    modelMatrix = glm::rotate(modelMatrix, pitch, PitchAxis);
    modelMatrix = glm::rotate(modelMatrix, roll, RollAxis);
    return modelMatrix;
}

void Entity::FixModelRotationOnLoad(glm::vec3 axis, float offSet)
{
    this->model->RotateYaw(offSet);

    float pitch = glm::radians(this->model->Pitch);
    float yaw = glm::radians(this->model->Yaw);
    float roll = glm::radians(this->model->Roll);

    modelMatrix = glm::rotate(modelMatrix, yaw, -YawAxis);
    modelMatrix = glm::rotate(modelMatrix, pitch, PitchAxis);
    modelMatrix = glm::rotate(modelMatrix, roll, RollAxis);
}

glm::vec3 Entity::GetDirection()
{

    return glm::vec3();
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

void Entity::SetIsTranslucid(bool isTranslucid)
{
    this->isTranslucid = isTranslucid;
}

bool Entity::GetIsTranslucid()
{
    return this->isTranslucid;
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