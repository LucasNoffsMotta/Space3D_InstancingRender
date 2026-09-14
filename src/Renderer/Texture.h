#pragma once

#include "stb_image.h"
#include<GLAD/glad.h>
#include<GLFW/glfw3.h>

class Texture
{
private:
	unsigned char* data;
	void LoadImageData(const char* filename);
	void ConfigureTextureBuffers();

public:
	GLuint texture;
	void ActiveTextureUnit(int unit);
	float width;
	float height;
	void BindTexture();
	void InitializeTexture(const char* filename, bool repeat = false);
	Texture(const char* filename, bool repeat = false);
	Texture();
};


