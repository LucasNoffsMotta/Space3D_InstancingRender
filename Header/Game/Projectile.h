#ifndef  PROJECTILE_CLASS_h
#define PROJECTILE_CLASS_H

#include "Renderer.h"
#include "Shader.h"

class Projectile {

private:
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 scale;
	glm::vec3 rotation;
	glm::vec3 color;
	float speed = 500.f;



public:
	float lifeSpan = 1000.f;
	float lifeTime = 0.f;
	Projectile(glm::vec3& color, glm::vec3& position, glm::vec3& scale, glm::vec3& rotation, glm::vec3& direction);
	~Projectile();
	void Draw(Renderer& renderer, Shader& shader);
	void Update();




};


#endif // ! PROJECTILE_CLASS_h

