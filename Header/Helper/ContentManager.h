#ifndef  CONTENT_MANAGER_CLASS_H
#define CONTENT_MANAGER_CLASS_H

#include "Render/Shader.h"
#include <map>
#include <Game/Camera.h>
#include "../../Texture.h"

static class ContentManager
{
public:
	static std::map<std::string, Shader>  Shaders;
	static std::map<std::string, glm::vec3> Colors;
	static std::map<std::string, Camera*> Cameras;
	static std::map<std::string, Texture*> Textures;

	static Shader LoadShader(const char* vertexSource, const char* fragmentSource, std::string shaderName);
	static glm::vec3 GetColor(std::string color);
	static void InsertColor(std::string name, glm::vec3 rgb);
	static Shader GetShader(std::string shader);
	static void InitColors();
	static void AddCamera(Camera* cam, std::string name);

};



#endif // ! CONTENT_MANAGER_CLASS_H
