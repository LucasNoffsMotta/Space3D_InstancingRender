#pragma once

#include "stb_image.h"
#include<GLAD/glad.h>
#include<GLFW/glfw3.h>
#include <string>
#include "../Helper/eTextureType.h"
#include <vector>




class Texture
{
private:


	void LoadImageDataFromFile(const char* filename, bool repeat, bool flip);

public:
	unsigned char* data;
	GLuint texture;
	void ActiveTextureUnit(int unit);
	void FlipTextureOnLoad();
	void SetTextureType(eTextureType type);
	float width;
	float height;
	std::string path;
	eTextureType type;
	void BindTexture();
	void InitializeTexture(const char* filename, bool repeat = false, bool flip = false);

	std::string TextureTypeToUniform(eTextureType type);


	void GenerateTexture(GLenum format, int width, int height, bool repeat, unsigned char* data = nullptr);
	void GenerateCubemapTexture(std::vector<std::string> texture_faces);

	void GenerateFramebufferTexture(GLenum format, int width, int height, bool repeat);
	Texture(const char* filename, bool repeat = false, bool flip = false);
	Texture();
	void AttatchToFramebuffer();
};


