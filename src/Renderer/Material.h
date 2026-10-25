#pragma once
#include "Texture.h"
#include <glm/glm.hpp>
#include <vector>

struct Material
{
	std::vector<Texture> textures;
	glm::vec4 color;
	float shininess = 20.f;
	float IndiceOfReflection = 0.f;

	Material(std::vector<Texture> _textures, glm::vec4 _color, float _shininess, float IOR)
	{
		textures = _textures;
		color = _color;
		shininess = _shininess;
		IndiceOfReflection = IOR;
	}

	Material() {}
};