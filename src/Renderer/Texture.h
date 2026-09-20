#pragma once

#include "stb_image.h"
#include<GLAD/glad.h>
#include<GLFW/glfw3.h>
#include <string>
#include "../Helper/eTextureType.h"




class Texture
{
private:


	void LoadImageData(const char* filename);

public:
	unsigned char* data;
	GLuint texture;
	void ActiveTextureUnit(int unit);
	void SetTextureType(eTextureType type);
	float width;
	float height;
	std::string path;
	eTextureType type;
	void BindTexture();
	void InitializeTexture(const char* filename, bool repeat = false);
	Texture(const char* filename, bool repeat = false);
	Texture();
};


