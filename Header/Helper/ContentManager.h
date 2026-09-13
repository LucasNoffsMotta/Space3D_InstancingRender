#ifndef  CONTENT_MANAGER_CLASS_H
#define CONTENT_MANAGER_CLASS_H

#include "Render/Shader.h"
#include <map>
#include <Game/Camera.h>
#include "../Texture.h"
#include "../PointLight.h"


static class ContentManager
{
public:
	static std::map<std::string, Shader>  Shaders;
	static std::map<std::string, glm::vec3> Colors;
	static std::map<std::string, Camera*> Cameras;
	static std::map<std::string, Texture*> Textures;
	static std::map<std::string, std::unique_ptr<PointLight>> PointLights;

	static Shader LoadShader(const char* vertexSource, const char* fragmentSource, std::string shaderName);
	static Texture* LoadTexture(const char* texturePath, std::string name);

	static glm::vec3 GetColor(std::string color);
	static void InsertColor(std::string name, glm::vec3 rgb);
	static Shader GetShader(std::string shader);
	static void InitColors();
	static void AddCamera(Camera* cam, std::string name);
	static void AddPointLight(int index);
};



#endif // ! CONTENT_MANAGER_CLASS_H
