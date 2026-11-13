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
};