#include "EditorUI.h"


// Helper to wire demo markers located in code to an interactive browser (e.g. https://pthom.github.io/imgui_explorer)
#if IMGUI_VERSION_NUM >= 19263
namespace ImGui { extern IMGUI_API void DemoMarker(const char* file, int line, const char* section); }
#define IMGUI_DEMO_MARKER(section)  do { ImGui::DemoMarker("imgui_demo.cpp", __LINE__, section); } while (0)
#endif

//Menu / UI Options:
//Lights
//Light color
//Light position


//Camera speed

void EditorUI::InitUI()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(ContentManager::mainWindow, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();
}

void EditorUI::ShowMainMenu()
{
    IMGUI_DEMO_MARKER("Examples/Menu");
    ImGui::MenuItem("(demo menu)", NULL, false, false);
    if (ImGui::MenuItem("New")) {  }
    if (ImGui::MenuItem("Open", "Ctrl+O")) {}
    if (ImGui::BeginMenu("Open Recent"))
    {
        ImGui::MenuItem("fish_hat.c");
        ImGui::MenuItem("fish_hat.inl");
        ImGui::MenuItem("fish_hat.h");
        if (ImGui::BeginMenu("More.."))
        {
            ImGui::MenuItem("Hello");
            ImGui::MenuItem("Sailor");
            if (ImGui::BeginMenu("Recurse.."))
            {
                ShowExampleMenuFile();
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Save", "Ctrl+S")) {}
    if (ImGui::MenuItem("Save As..")) {}

    ImGui::Separator();

    /*
    // LIGHT OPTIONS
    */

    if (ImGui::BeginMenu("Light Options"))
    {
        ImGui::BeginChild("child", ImVec2(0, ImGui::GetTextLineHeightWithSpacing() * 20.0f), ImGuiChildFlags_Borders);

        for (int i = 0; i < ContentManager::MAX_POINT_LIGHTS; i++)
        {
            std::string id = std::to_string(i);
            ImGui::Text("Point Light %id", id);
            ImGui::Text("Color %id", id);
            EditorUI::CreateLightColorOptions(id);
            EditorUI::CreateLightDiffuseOptions(id);
            EditorUI::CreateLightSpecularOptions(id);
            ImGui::Text("Attenuation %id", id);
            EditorUI::CreateLightLinearAttenuationOption(id);
            EditorUI::CreateLightQuadraticAttenuationOption(id);
            ImGui::Separator();
        }

        ImGui::EndChild();
        ImGui::EndMenu();
    }

    /*
    //  CAMERA OPTIONS
    */

    if (ImGui::BeginMenu("Camera Options"))
    {
        static bool mouseEnabled = true;
        ImGui::MenuItem("Mouse Enabled", "", &mouseEnabled);
        ContentManager::IsMouseEnabled = mouseEnabled;
    
        static float f = 10.f;
        static int n = 0;
        ImGui::SliderFloat("Camera Speed", &f, 0.0f, 10000.0f);
        ContentManager::Cameras["main"]->SetMoveSpeed(f);

        ImGui::InputFloat("Speed", &f, 0.1f);
        ImGui::EndMenu();
    }

    //if (ImGui::BeginMenu("Colors"))
    //{
    //    IMGUI_DEMO_MARKER("Examples/Menu/Colors");
    //    float sz = ImGui::GetTextLineHeight();
    //    for (int i = 0; i < ImGuiCol_COUNT; i++)
    //    {
    //        const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
    //        ImVec2 p = ImGui::GetCursorScreenPos();
    //        ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
    //        ImGui::Dummy(ImVec2(sz, sz));
    //        ImGui::SameLine();
    //        ImGui::MenuItem(name);
    //    }
    //    ImGui::EndMenu();
    //}

    if (ImGui::BeginMenu("Disabled", false)) // Disabled
    {
        IM_ASSERT(0);
    }
    if (ImGui::MenuItem("Checked", NULL, true)) {}
    ImGui::Separator();
    if (ImGui::MenuItem("Quit", "Alt+F4")) 
    {
        ContentManager::Cameras["main"]->SetIsPaused(false);
        ContentManager::SetMouseInputMode(ContentManager::IsMouseEnabled);;
    }
}

void EditorUI::ShowExampleMenuFile()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            IMGUI_DEMO_MARKER("Menu/File");
            ShowExampleMenuFile();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            IMGUI_DEMO_MARKER("Menu/Edit");
            if (ImGui::MenuItem("Undo", "Ctrl+Z")) {}
            if (ImGui::MenuItem("Redo", "Ctrl+Y", false, false)) {} // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "Ctrl+X")) {}
            if (ImGui::MenuItem("Copy", "Ctrl+C")) {}
            if (ImGui::MenuItem("Paste", "Ctrl+V")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void EditorUI::StartUIFrame()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

}

void EditorUI::EndUIFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EditorUI::ClearResources()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void EditorUI::CreateLightColorOptions(std::string id)
{
    std::string colorId = ("Color R##" + id);
    ImGui::SliderFloat(colorId.c_str(), &ContentManager::PointLights[id]->GetColor().r, 0.0f, 1.f);

    colorId = ("Color G##" + id);
    ImGui::SliderFloat(colorId.c_str(), &ContentManager::PointLights[id]->GetColor().g, 0.0f, 1.f);

    colorId = ("Color B##" + id);
    ImGui::SliderFloat(colorId.c_str(), &ContentManager::PointLights[id]->GetColor().b, 0.0f, 1.f);
}

void EditorUI::CreateLightDiffuseOptions(std::string id)
{
    std::string colorId = ("Diffuse R##" + id);
    ImGui::SliderFloat(colorId.c_str(), &ContentManager::PointLights[id]->GetDiffuse().r, 0.0f, 1.f);

    colorId = ("Diffuse G##" + id);
    ImGui::SliderFloat(colorId.c_str(), &ContentManager::PointLights[id]->GetDiffuse().g, 0.0f, 1.f);

    colorId = ("Diffuse B##" + id);
    ImGui::SliderFloat(colorId.c_str(), &ContentManager::PointLights[id]->GetDiffuse().b, 0.0f, 1.f);
}

void EditorUI::CreateLightSpecularOptions(std::string id)
{
    std::string colorId = ("Specular R##" + id);
    ImGui::SliderFloat(colorId.c_str(), &ContentManager::PointLights[id]->GetSpecular().r, 0.0f, 1.f);

    colorId = ("Specular G##" + id);
    ImGui::SliderFloat(colorId.c_str(), &ContentManager::PointLights[id]->GetSpecular().g, 0.0f, 1.f);

    colorId = ("Specular B##" + id);
    ImGui::SliderFloat(colorId.c_str(), &ContentManager::PointLights[id]->GetSpecular().b, 0.0f, 1.f);
}

void EditorUI::CreateLightAmbientOptions(std::string id)
{
    std::string colorId = ("Ambient R##" + id);
    ImGui::SliderFloat(colorId.c_str(), &ContentManager::PointLights[id]->GetAmbient().r, 0.0f, 1.f);

    colorId = ("Ambient G##" + id);
    ImGui::SliderFloat(colorId.c_str(), &ContentManager::PointLights[id]->GetAmbient().g, 0.0f, 1.f);

    colorId = ("Ambient B##" + id);
    ImGui::SliderFloat(colorId.c_str(), &ContentManager::PointLights[id]->GetAmbient().b, 0.0f, 1.f);
}

void EditorUI::CreateLightLinearAttenuationOption(std::string id)
{
    std::string LinearID = ("Linear R##" + id);
    ImGui::InputFloat(LinearID.c_str(), &ContentManager::PointLights[id]->GetLinear(), 0.09f);
}

void EditorUI::CreateLightQuadraticAttenuationOption(std::string id)
{
    std::string LinearID = ("Quadratic R##" + id);
    ImGui::InputFloat(LinearID.c_str(), &ContentManager::PointLights[id]->GetQuadratic(), 0.032f);
}
