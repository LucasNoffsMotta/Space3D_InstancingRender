#include "Renderer.h"
#include "Renderer.h"
#include "../OpenGL/VAO.h"
#include "stb_image.h"
#include "../Helper/ContentManager.h"



void Renderer::BindFrameBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void Renderer::UnbindFramebuffer()
{
    glClearBufferiv(GL_FRAMEBUFFER, fbo, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void Renderer::BindEnviromentFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, enviromnentFrameBuffer);
}

void Renderer::UnbindEnviromentFramebuffer()
{
    glClearBufferiv(GL_FRAMEBUFFER, enviromnentFrameBuffer, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void Renderer::InitFrameBufferScreenQuad()
{
    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates. NOTE that this plane is now much smaller and at the top of the screen
        // positions   // texCoords
        -0.3f,  1.0f,  0.0f, 1.0f,
        -0.3f,  0.7f,  0.0f, 0.0f,
         0.3f,  0.7f,  1.0f, 0.0f,

        -0.3f,  1.0f,  0.0f, 1.0f,
         0.3f,  0.7f,  1.0f, 0.0f,
         0.3f,  1.0f,  1.0f, 1.0f
    };


    // screen quad VAO
    unsigned int quadVBO;
    glGenVertexArrays(1, &frameBufferVao);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(frameBufferVao);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

void Renderer::InitFramebufferTexture()
{
    frameBufferTexture = new Texture();
    frameBufferTexture->GenerateFramebufferTexture(ContentManager::FRAMEBUFFER_SCREEN_SIZE_X, ContentManager::FRAMEBUFFER_SCREEN_SIZE_Y);
}

void Renderer::InitEnviromentMapTexture()
{
    enviromentMapTexture = new Texture();
    enviromentMapTexture->GenerateEnviromentMapTexture(ContentManager::FRAMEBUFFER_SCREEN_SIZE_X, ContentManager::FRAMEBUFFER_SCREEN_SIZE_X); //Got to be a square in order to work!
}

void Renderer::RenderFramebuffer(Shader& shader)
{
    frameBufferTexture->BindTexture();
    shader.Activate();
    shader.SetUniformInt("postProcessEffect", ContentManager::GlobalPostProcessMode);
    glBindVertexArray(frameBufferVao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

Texture* Renderer::GetFramebufferTexture()
{
    return frameBufferTexture;
}

void Renderer::AttatchTextureToFramebuffer()
{
    frameBufferTexture->AttatchToFramebuffer();
}

void Renderer::AttatchEnviromentMapToFramebuffer()
{
    enviromentMapTexture->AttatchCubemapFaceToFramebuffer();
}

Renderer::Renderer()
{
}

void Renderer::ScreenShot(const char* filePath, GLFWwindow* window)
{
    GLsizei nrChannels = 3;
    GLsizei stride = nrChannels * ContentManager::FRAMEBUFFER_SCREEN_SIZE_X;
    stride += (stride % 4) ? (4 - stride % 4) : 0;

    GLsizei bufferSize = stride * ContentManager::FRAMEBUFFER_SCREEN_SIZE_Y;
    std::vector<char> buffer(bufferSize);

    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glReadBuffer(GL_BACK);
    glReadPixels(0, 0, ContentManager::FRAMEBUFFER_SCREEN_SIZE_X, ContentManager::FRAMEBUFFER_SCREEN_SIZE_Y, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());
    //stbi_flip_vertically_on_write(true);
    stbi_write_png(filePath, ContentManager::FRAMEBUFFER_SCREEN_SIZE_X, ContentManager::FRAMEBUFFER_SCREEN_SIZE_Y, nrChannels, buffer.data(), stride);
}

void Renderer::RenderDisplayModel(Shader* shader)
{
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, ModelDisplayPos);
    modelMatrix = glm::scale(modelMatrix, ModelDisplayScale);

    ModelDisplayRotationOffset+=0.01f;
    if (ModelDisplayRotationOffset >= 360) ModelDisplayRotationOffset = 0;

    modelMatrix = glm::rotate(modelMatrix, ModelDisplayRotationOffset, glm::vec3(0,1,0));
    glm::mat4 view = glm::mat4(1);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    shader->Activate();
    shader->SetUniformMatrix4fv("model", modelMatrix);
    shader->SetUniformMatrix4fv("fixedView", view);
    DisplayModels[currentDisplayedModelIndex]->Draw(*shader);
}


void Renderer::GetAllLoadedModels()
{
    for (auto const& [key, val] : ContentManager::Models)
    {
        DisplayModels.push_back(val);
    }
}

void Renderer::GetInput()
{
    if (ContentManager::Controllers["main"]->Inputs[eInput::Space_Bar])
    {
        if (currentDisplayedModelIndex + 1 >= DisplayModels.size()) currentDisplayedModelIndex = 0;

        else
        {
            currentDisplayedModelIndex += 1;
        }   
    }



    if (ContentManager::Controllers["main"]->Inputs[eInput::Enter])
    {
        /*if (DisplayModels.at(currentDisplayedModelIndex))
        {
            Model* model = DisplayModels.at(currentDisplayedModelIndex);
            ContentManager::CreateEntity(eHierarchyLevel::NO_STENCIL_TEST, model, ContentManager::Cameras["main"]->CameraPos, glm::vec3(1), 0, false, false);
            ContentManager::newEntityAdded = true;
            return;
        }*/

        ScreenShot(("D:/Projetos/c++/OpenGL/VoidEngine/src/print_" + std::to_string(screenShotTaken) + ".png").c_str(), ContentManager::mainWindow);
        screenShotTaken++;
    }
}

void Renderer::InitFrameBuffer()
{
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void Renderer::InitRenderBuffer(int frameBufferSizeX, int frameBufferSizeY)
{

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, frameBufferSizeX, frameBufferSizeY);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::InitEnviromentFramebuffer()
{
    glGenFramebuffers(1, &enviromnentFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, enviromnentFrameBuffer);
}

void Renderer::InitEnviromentRenderbuffer()
{
    glGenRenderbuffers(1, &enviromnentRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, enviromnentRenderBuffer);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, ContentManager::FRAMEBUFFER_SCREEN_SIZE_X, ContentManager::FRAMEBUFFER_SCREEN_SIZE_X);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, enviromnentRenderBuffer);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::InitUniformBufferObjects()
{
    glGenBuffers(1, &uboMatrices);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);


    glGenBuffers(1, &uboDirLight);
    glBindBuffer(GL_UNIFORM_BUFFER, uboDirLight);
    glBufferData(GL_UNIFORM_BUFFER, 4 * sizeof(glm::vec3), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    SetShadersBindingPointToUseUniformBuffer();
}

void Renderer::SetShadersBindingPointToUseUniformBuffer()
{
    //Matrices Uniform
    unsigned int ubo_FullRender_Matrices = glGetUniformBlockIndex(ContentManager::Shaders[eRenderMode::FullRender]->Id, "Matrices");
    unsigned int ubo_Outline_Matrices = glGetUniformBlockIndex(ContentManager::Shaders[eRenderMode::Outline]->Id, "Matrices");
    unsigned int ubo_Instanced_Matrices = glGetUniformBlockIndex(ContentManager::Shaders[eRenderMode::FullRender_Instanced]->Id, "Matrices");
    unsigned int ubo_SkyBox_Matrices = glGetUniformBlockIndex(ContentManager::Shaders[eRenderMode::SkyBox]->Id, "Matrices");
    unsigned int ubo_FullRender_GeometryShader_Matrices = glGetUniformBlockIndex(ContentManager::Shaders[eRenderMode::RenderNormals_GeometryShader]->Id, "Matrices");
    unsigned int ubo_DisplayModel_Matrices = glGetUniformBlockIndex(ContentManager::Shaders[eRenderMode::ModelDisplay]->Id, "Matrices");

    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));
    glUniformBlockBinding(ContentManager::Shaders[eRenderMode::FullRender]->Id, ubo_FullRender_Matrices, 0);
    glUniformBlockBinding(ContentManager::Shaders[eRenderMode::Outline]->Id, ubo_Outline_Matrices, 0);
    glUniformBlockBinding(ContentManager::Shaders[eRenderMode::FullRender_Instanced]->Id, ubo_Instanced_Matrices, 0);
    glUniformBlockBinding(ContentManager::Shaders[eRenderMode::SkyBox]->Id, ubo_SkyBox_Matrices, 0);
    glUniformBlockBinding(ContentManager::Shaders[eRenderMode::RenderNormals_GeometryShader]->Id, ubo_FullRender_GeometryShader_Matrices, 0);
    glUniformBlockBinding(ContentManager::Shaders[eRenderMode::ModelDisplay]->Id, ubo_DisplayModel_Matrices, 0);

    //Dir Light Uniform
    unsigned int ubo_FullRender_DirLight = glGetUniformBlockIndex(ContentManager::Shaders[eRenderMode::FullRender]->Id, "DirLight");
    unsigned int ubo_Instanced_DirLight = glGetUniformBlockIndex(ContentManager::Shaders[eRenderMode::FullRender_Instanced]->Id, "DirLight");
    unsigned int ubo_SkyBox_DirLight = glGetUniformBlockIndex(ContentManager::Shaders[eRenderMode::SkyBox]->Id, "DirLight");

    glBindBufferRange(GL_UNIFORM_BUFFER, 1, uboDirLight, 0, 4 * sizeof(glm::vec3));
    glUniformBlockBinding(ContentManager::Shaders[eRenderMode::FullRender]->Id, ubo_FullRender_DirLight, 1);
    glUniformBlockBinding(ContentManager::Shaders[eRenderMode::SkyBox]->Id, ubo_SkyBox_DirLight, 1);
    glUniformBlockBinding(ContentManager::Shaders[eRenderMode::FullRender_Instanced]->Id, ubo_Instanced_DirLight, 1);
}

void Renderer::FillUboMatricesProjection(glm::mat4 projection)
{
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Renderer::FillUboDirLight(DirectionalLight& light)
{
    glBindBuffer(GL_UNIFORM_BUFFER, uboDirLight);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec3), glm::value_ptr(light.GetDirection()));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec3), sizeof(glm::vec3), glm::value_ptr(light.GetAmbient()));
    glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec3), sizeof(glm::vec3), glm::value_ptr(light.GetDiffuse()));
    glBufferSubData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::vec3), sizeof(glm::vec3), glm::value_ptr(light.GetSpecular()));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Renderer::FillUboMatricesView(glm::mat4 view)
{
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
