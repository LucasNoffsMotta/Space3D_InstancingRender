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

const int LIGHT_MENU_SIZE = 300;

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
        ImGui::BeginChild("child", ImVec2(LIGHT_MENU_SIZE, LIGHT_MENU_SIZE), ImGuiChildFlags_Borders);

        for (int i = 0; i < ContentManager::MAX_POINT_LIGHTS; i++)
        {
            std::string id = std::to_string(i);
            ImGui::Text("Point Light %id", id);
            ImGui::Text("Color %id", id);
            EditorUI::CreateLightColorOptions(id, ContentManager::PointLights[id]->GetColor());
            EditorUI::CreateLightDiffuseOptions(id, ContentManager::PointLights[id]->GetDiffuse());
            EditorUI::CreateLightSpecularOptions(id, ContentManager::PointLights[id]->GetSpecular());
            EditorUI::CreateLightAmbientOptions(id, ContentManager::PointLights[id]->GetAmbient());
            ImGui::Text("Attenuation %id", id);
            EditorUI::CreateLightLinearAttenuationOption(id);
            EditorUI::CreateLightQuadraticAttenuationOption(id);
            ImGui::Separator();
        }

        ///DIR LIGHT

        ImGui::Text("Direct Light");
        ImGui::Text("Color");
        EditorUI::CreateLightColorOptions("DirectLightColor", ContentManager::DirectionalLights["0"]->GetColor());
        EditorUI::CreateLightDiffuseOptions("DirectLightDiffuse", ContentManager::DirectionalLights["0"]->GetDiffuse());
        EditorUI::CreateLightSpecularOptions("DirectLightSpecular", ContentManager::DirectionalLights["0"]->GetSpecular());
        EditorUI::CreateLightAmbientOptions("DirectLightAmbient", ContentManager::DirectionalLights["0"]->GetAmbient());

        ImGui::Text("Direction");
        EditorUI::CreateLightDirectionOptions("Direction");

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

void EditorUI::CreateLightColorOptions(std::string id, glm::vec3& rgb)
{
    std::string colorId = ("Color R##" + id);
    ImGui::SliderFloat(colorId.c_str(), &rgb.x, 0.0f, 1.f);

    colorId = ("Color G##" + id);
    ImGui::SliderFloat(colorId.c_str(), &rgb.y, 0.0f, 1.f);

    colorId = ("Color B##" + id);
    ImGui::SliderFloat(colorId.c_str(), &rgb.z, 0.0f, 1.f);
}

void EditorUI::CreateLightDiffuseOptions(std::string id, glm::vec3& rgb)
{
    std::string colorId = ("Diffuse R##" + id);
    ImGui::SliderFloat(colorId.c_str(), &rgb.x, 0.0f, 1.f);

    colorId = ("Diffuse G##" + id);
    ImGui::SliderFloat(colorId.c_str(), &rgb.y, 0.0f, 1.f);

    colorId = ("Diffuse B##" + id);
    ImGui::SliderFloat(colorId.c_str(), &rgb.z, 0.0f, 1.f);
}

void EditorUI::CreateLightSpecularOptions(std::string id, glm::vec3& rgb)
{
    std::string colorId = ("Specular R##" + id);
    ImGui::SliderFloat(colorId.c_str(), &rgb.x, 0.0f, 1.f);

    colorId = ("Specular G##" + id);
    ImGui::SliderFloat(colorId.c_str(), &rgb.y, 0.0f, 1.f);

    colorId = ("Specular B##" + id);
    ImGui::SliderFloat(colorId.c_str(), &rgb.z, 0.0f, 1.f);
}

void EditorUI::CreateLightAmbientOptions(std::string id, glm::vec3& rgb)
{
    std::string colorId = ("Ambient R##" + id);
    ImGui::SliderFloat(colorId.c_str(), &rgb.x, 0.0f, 1.f);

    colorId = ("Ambient G##" + id);
    ImGui::SliderFloat(colorId.c_str(), &rgb.y, 0.0f, 1.f);

    colorId = ("Ambient B##" + id);
    ImGui::SliderFloat(colorId.c_str(), &rgb.z, 0.0f, 1.f);
}

void EditorUI::CreateLightDirectionOptions(std::string id)
{
    glm::vec3 newDir = ContentManager::DirectionalLights["0"]->GetDirection();

    ImGui::InputFloat("X: ", &newDir.x);
    ImGui::InputFloat("Y: ", &newDir.y);
    ImGui::InputFloat("Z: ", &newDir.z);

    newDir = glm::normalize(newDir);
    ContentManager::DirectionalLights["0"]->SetDirection(newDir) ;
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

