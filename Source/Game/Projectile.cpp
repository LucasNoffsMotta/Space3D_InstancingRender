#include "Game/Projectile.h"
#include "Helper/TimeHelper.h"
#include <Render/Shader.h>

Projectile::Projectile(glm::vec3& color, glm::vec3& position, glm::vec3& scale, glm::vec3& rotation, glm::vec3& direction)
{
	this->color = color;
	this->position = position;
	this->scale = scale;
	this->rotation = rotation;
	this->direction = direction;
}

Projectile::~Projectile()
{
}

void Projectile::Update()
{
	position += direction * speed * TimeHelper::GetDeltaTime();
	lifeTime++;
}

void Projectile::Draw(Renderer& renderer, Shader& shader)
{
	renderer.DrawBullet(position, scale, rotation, 0.f, color, shader);
}
