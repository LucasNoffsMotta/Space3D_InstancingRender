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
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::InitializeTexture(const char* filename, bool repeat, bool flip)
{
	LoadImageData(filename, repeat, flip);
}

void Texture::LoadImageData(const char* filename, bool repeat, bool flip)
{
	int width, height, nrChannels;

	std::ifstream test(filename);
	if (!test.is_open()) {
		std::cout << "Arquivo não encontrado: " << filename << std::endl;
	}

	if (flip) FlipTextureOnLoad();

	glGenTextures(1, &texture);
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


		this->width = width;
		this->height = height;

	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
}