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
	int hasTexture = 0;
	int hasReflection = 0;
	int useColor = 1;
	bool useSpecular = false;

	Material(std::vector<Texture> _textures, glm::vec4 _color, float _shininess, float IOR)
	{
		textures = _textures;
		color = _color;
		shininess = _shininess;
		IndiceOfReflection = IOR;
		SetHasTexture();
		SetHasReflection();
		SetUseColor();
	}

	Material() {}

	void SetMaterialProperties()
	{
		SetHasTexture();
		SetHasReflection();
		SetUseColor();
		SetUseSpecular();
	}

	void SetUseSpecular()
	{
		for (int i = 0; i < textures.size(); i++)
		{
			if (textures[i].type == eTextureType::Specular)
			{
				useSpecular = true;
				return;
			}
		}
	}

	void SetHasTexture()
	{
		this->hasTexture = textures.size() > 0 ? 1 : 0;
	}

	void SetHasReflection()
	{
		for (int i = 0; i < textures.size(); i++)
		{
			if (textures[i].type == eTextureType::Diffuse_CubeMap)
			{
				hasReflection = 1;
				return;
			}
		}

		hasReflection = 0;
	}

	void SetUseColor()
	{
		if (textures.size() == 1 && textures[0].type == eTextureType::Diffuse_CubeMap) useColor = 1; //USE COLOR IF THE ONLY TEXTURE IS FOR REFLECTION (IT WILL MIX THE COLOR AND REFLECTION INSIDE THE SHADER)!
		else if (textures.size() > 0) useColor = 0;
		else
		{
			useColor = 1;
		}
	}
};