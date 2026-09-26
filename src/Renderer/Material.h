#pragma once
#include "Texture.h"
#include <glm/glm.hpp>
#include <vector>

struct Material
{
	std::vector<Texture> textures;
	glm::vec3 color;
	float shininess = 20.f;

	Material(std::vector<Texture> _textures, glm::vec3 _color, float _shininess)
	{
		textures = _textures;
		color = _color;
		shininess = _shininess;
	}

	Material() {}
};