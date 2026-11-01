#include "Renderer.h"
#include "Renderer.h"
#include "../OpenGL/VAO.h"
#include "../Helper/ContentManager.h"



void Renderer::BindFrameBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void Renderer::UnbindFramebuffer()
{
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
    frameBufferTexture = Texture();
    frameBufferTexture.GenerateFramebufferTexture(GL_RGB, ContentManager::FRAMEBUFFER_SCREEN_SIZE_X, ContentManager::FRAMEBUFFER_SCREEN_SIZE_Y, false);
    frameBufferTexture.AttatchToFramebuffer();
}

void Renderer::RenderFramebuffer(Shader& shader)
{
    frameBufferTexture.BindTexture();
    shader.Activate();
    shader.SetUniformInt("postProcessEffect", ContentManager::GlobalPostProcessMode);
    glBindVertexArray(frameBufferVao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

Texture& Renderer::GetFramebufferTexture()
{
    return frameBufferTexture;
}

Renderer::Renderer()
{
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

    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));
    glUniformBlockBinding(ContentManager::Shaders[eRenderMode::FullRender]->Id, ubo_FullRender_Matrices, 0);
    glUniformBlockBinding(ContentManager::Shaders[eRenderMode::Outline]->Id, ubo_Outline_Matrices, 0);
    glUniformBlockBinding(ContentManager::Shaders[eRenderMode::FullRender_Instanced]->Id, ubo_Instanced_Matrices, 0);
    glUniformBlockBinding(ContentManager::Shaders[eRenderMode::SkyBox]->Id, ubo_SkyBox_Matrices, 0);

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
