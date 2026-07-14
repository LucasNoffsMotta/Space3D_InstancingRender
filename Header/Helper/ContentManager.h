#ifndef  CONTENT_MANAGER_CLASS_H
#define CONTENT_MANAGER_CLASS_H

#include "Shader.h"
#include <map>

static class ContentManager
{
public:
	static std::map<std::string, Shader>  Shaders;
	static std::map<std::string, glm::vec3> Colors;
	static Shader LoadShader(const char* vertexSource, const char* fragmentSource, std::string shaderName);
	static glm::vec3 GetColor(std::string color);
	static void InsertColor(std::string name, glm::vec3 rgb);
	static Shader GetShader(std::string shader);
	static void InitColors();

};



#endif // ! CONTENT_MANAGER_CLASS_H
