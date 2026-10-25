#include "Texture.h"
#include <iostream>
#include <fstream>
#include <gl/GL.h>


Texture::Texture(const char* filename, bool repeat, bool flip)
{
	InitializeTexture(filename, repeat, flip);
}

Texture::Texture()
{
	//
}

void Texture::AttatchToFramebuffer()
{
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
}

void Texture::ActiveTextureUnit(int unit)
{
     glActiveTexture(GL_TEXTURE0 + unit);
}

void Texture::FlipTextureOnLoad()
{
	stbi_set_flip_vertically_on_load(true);
}

void Texture::SetTextureType(eTextureType type)
{
	this->type = type;
}

void Texture::BindTexture()
{
	if (type == eTextureType::Diffuse_CubeMap)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
		return;
	}

	glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::InitializeTexture(const char* filename, bool repeat, bool flip)
{
	LoadImageDataFromFile(filename, repeat, flip);
}

std::string Texture::TextureTypeToUniform(eTextureType type)
{
	switch (type)
	{
	case Diffuse:
		return "texture_diffuse";
		break;
	case Specular:
		return "texture_specular";
		break;
	case Diffuse_CubeMap:
		return "skybox";
		break;
	default:
		return "none";
		break;
	}
}

void Texture::GenerateTexture(GLenum format, int width, int height, bool repeat, unsigned char* data)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	if (repeat)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::GenerateCubemapTexture(std::vector<std::string> texture_faces)
{
	int width, height, nrChannels;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	for (int i = 0; i < texture_faces.size(); i++)
	{
		unsigned char* data = stbi_load(texture_faces.at(i).c_str(), &width, &height, &nrChannels, 0);

		if (data)
		{
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
		}

		else
		{
			std::cout << "Cubemap tex failed to load at path: " << texture_faces.at(i) << std::endl;
		}
		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Texture::GenerateFramebufferTexture(GLenum format, int width, int height, bool repeat)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::LoadImageDataFromFile(const char* filename, bool repeat, bool flip)
{
	int width, height, nrChannels;

	std::ifstream test(filename);
	if (!test.is_open()) {
		std::cout << "Arquivo não encontrado: " << filename << std::endl;
	}

	if (flip) FlipTextureOnLoad();

	data = stbi_load(filename, &width, &height, &nrChannels, 0);

	if (data)
	{
		GLenum format;

		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		GenerateTexture(format, width, height, repeat, data);

		this->width = width;
		this->height = height;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
}