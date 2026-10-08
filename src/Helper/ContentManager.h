#ifndef  CONTENT_MANAGER_CLASS_H
#define CONTENT_MANAGER_CLASS_H

#include "../Renderer/Shader.h"
#include <map>
#include "../Renderer/Camera.h"
#include "../Renderer/Texture.h"
#include "../Renderer/Model.h"
#include "InputManager.h"
#include "../Renderer/BaseLight.h"
#include "../Renderer/PointLight.h"
#include "../Renderer/SpotLight.h"
#include "../Renderer/DirectionalLight.h"
#include "glm/glm.hpp"
#include "../Renderer/Entity.h"


static class ContentManager
{
public:
	static std::map<std::string, Shader*>  Shaders;
	static std::map<std::string, glm::vec3> Colors;
	static std::map<std::string, Camera*> Cameras;
	static std::map<std::string, Texture*> Textures;
	static std::map<std::string, std::unique_ptr<DirectionalLight>> DirectionalLights;
	static std::map<std::string, std::unique_ptr<PointLight>> PointLights;
	static std::map<std::string, std::unique_ptr<SpotLight>> SpotLights;
	static std::map<std::string, Model*> Models;

	static std::map<eHierarchyLevel, std::vector<Entity*>> Entities;

	

	static std::map<std::string, InputManager*> Controllers;
	static GLFWwindow* mainWindow;
	static const int SCR_WIDTH = 1920;
	static const int SCR_HEIGHT = 1920;
	static const int MAX_POINT_LIGHTS = 10;

	static Shader* LoadShader(const char* vertexSource, const char* fragmentSource, std::string shaderName);
	static Texture* LoadTexture(const char* texturePath, std::string name);
	static Model* LoadModel(const char* modelPath, std::string name);

	static glm::vec3 GetColor(std::string color);
	static void InsertColor(std::string name, glm::vec3 rgb);
	static Shader* GetShader(std::string shader);
	static void InitColors();
	static void CreateEntity(eHierarchyLevel level, Model* model, glm::vec3 pos, glm::vec3 scale, float rotation, bool outline);
	static void AddCamera(Camera* cam, std::string name);
	static void AddPointLight(int index);
	static void AddSpotLight(int index);
	static void AddDirectionalLight(int index);
	static void AddController(std::string name);
	static void SetMainWindow(GLFWwindow* window);
};



#endif // ! CONTENT_MANAGER_CLASS_H
