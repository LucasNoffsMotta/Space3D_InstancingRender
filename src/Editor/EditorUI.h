#pragma once

#include "../Helper/ContentManager.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


/// <summary>
/// Interface with ImGui API
/// </summary>
static class EditorUI
{
public:
	static void InitUI();
	static void ShowMainMenu();
	static void ShowExampleMenuFile();
	static void StartUIFrame();
	static void EndUIFrame();
	static void ClearResources();

	//Point / Dir / Spot Light
	static void CreateLightColorOptions(std::string id, glm::vec3& rgb);
	static void CreateLightDiffuseOptions(std::string id, glm::vec3& rgb);
	static void CreateLightSpecularOptions(std::string id, glm::vec3& rgb);
	static void CreateLightAmbientOptions(std::string id, glm::vec3& rgb);

	//DirLight
	static void CreateLightDirectionOptions(std::string id);

	static void CreateLightLinearAttenuationOption(std::string id);
	static void CreateLightQuadraticAttenuationOption(std::string id);
};