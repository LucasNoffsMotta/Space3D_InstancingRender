#include "Renderer.h"
#include "../OpenGL/VAO.h"
#include "../Helper/ContentManager.h"



void Renderer::InitCubeWithNormalsAndTextureRenderData()
{
    float square[] = { 
        //Position          //Color        // Normal            //Text
        -0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0, 0.f,   0.0f, -1.0f,     0.0f,  0.0f,
         0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0, 0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
         0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0, 0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
         0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0, 0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0, 0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0, 0.0f,  0.0f, -1.0f,     0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f, 1.0, 1.0, 1.0,  0.0f,  0.0f,    1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f, 1.0, 0.1, 1.0, 0.0f,  0.0f,    1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0,  0.0f,  0.0f,   1.0f, 1.0f,  1.0f,
         0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0, 0.0f,  0.0f,     1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0, 0.0f,  0.0f,    1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, 1.0, 1.0, 1.0, 0.0f,  0.0f,    1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0, -1.0f,  0.0f,   0.0f, 1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0, -1.0f,  0.0f,   0.0f, 1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0, -1.0f,  0.0f,   0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0, -1.0f,  0.0f,   0.0f,   0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, 1.0, 1.0, 1.0,  -1.0f,  0.0f,  0.0f, 0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0, -1.0f,  0.0f,   0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0, 1.0f,  0.0f,   0.0f, 1.0f,  0.0f,
         0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0, 1.0f,  0.0f,   0.0f, 1.0f,  1.0f,
         0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0,  1.0f,  0.0f,  0.0f, 0.0f,  1.0f,
         0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0, 1.0f,  0.0f,   0.0f, 0.0f,  1.0f,
         0.5f, -0.5f,  0.5f, 1.0, 1.0, 1.0, 1.0f,  0.0f,   0.0f, 0.0f,  0.0f,
         0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0, 0.0f, -1.0f,   0.0f, 1.0f,  1.0f,
         0.5f, -0.5f,  0.5f, 1.0, 1.0, 1.0, 0.0f, -1.0f,   0.0f, 1.0f,  0.0f,
         0.5f, -0.5f,  0.5f, 1.0, 1.0, 1.0, 0.0f, -1.0f,   0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, 1.0, 1.0, 1.0, 0.0f, -1.0f,   0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0, 0.0f, -1.0f,   0.0f, 0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0, 0.0f,  1.0f,   0.0f, 0.0f,  1.0f,
         0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0, 0.0f,  1.0f,   0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0, 0.0f,  1.0f,   0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0,  0.0f,  1.0f,  0.0f, 1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0, 0.0f,  1.0f,   0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0,  0.0f,  1.0f,   0.0f, 0.0f,  1.0f
    };

    vao = VAO();
    VBO vbo = VBO(square, sizeof(square));
    vao.Bind();
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(float) * 11, (void*)0);
    vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(float) * 11, (void*)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 3, 3, GL_FLOAT, sizeof(float) * 11, (void*)(6 * sizeof(float)));
    vao.LinkAttrib(vbo, 4, 2, GL_FLOAT, sizeof(float) * 11, (void*)(9 * sizeof(float)));
}

void Renderer::InitViewAndProjectionMatrices()
{
    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)1920 / 1200, 0.1f, 6000.f);
}

void Renderer::InitQuad2DRenderData()
{
    float aimDot[] = {
       -0.5f, -0.5f, -0.5f, 
        0.5f, -0.5f, -0.5f, 
        0.5f,  0.5f, -0.5f, 
        0.5f,  0.5f, -0.5f, 
       -0.5f,  0.5f, -0.5f, 
       -0.5f, -0.5f, -0.5f, 
    };


    aimDotVao = VAO();
    VBO vbo = VBO(aimDot, sizeof(aimDot));
    aimDotVao.Bind();
    aimDotVao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(float) * 3, (void*)0);
}

void Renderer::InitQuad3DRenderData()
{
    float square[] = {
        //Position          //Color       
        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f, 
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f, 
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f, 
        -0.5f, -0.5f,  0.5f, 

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f, 

        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f,  0.5f, 
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f, 
        -0.5f, -0.5f, -0.5f, 

        -0.5f,  0.5f, -0.5f, 
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f, 
         0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f, 
    };

    vao = VAO();
    VBO vbo = VBO(square, sizeof(square));
    vao.Bind();
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(float) * 3, (void*)0);
}

Renderer::Renderer()
{
    InitViewAndProjectionMatrices();
    CreatePointLights();
    CreateSpotLights();
    CreateDirectionalLights();
}

void Renderer::SetModelMatrices(glm::vec3* translations, int ammount)
{
    modelMatrices = new glm::mat4[ammount];
    glm::vec3* dummtPtr = translations;

    for (int i = 0; i < ammount; i++)
    {
        glm::vec3 trans = *dummtPtr;
        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model, trans);
        model = glm::scale(model, glm::vec3(100));
        modelMatrices[i] = model;
        float scale = static_cast<float>((rand() % 20) / 100.0 + 0.05);
        model = glm::scale(model, glm::vec3(scale));
        dummtPtr++;
    }
}

void Renderer::SetInstancesBuffers(int amount)
{
    SetModelMatrices(instancesTranslationPtr, amount);
    vao.LinkInstancedMat4(modelMatrices, amount);
}

void Renderer::Draw(glm::vec3 translation, Texture& texture, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 color, Shader& shader)
{
    //Keep on draw:
    shader.Activate();
    texture.ActiveTextureUnit(0);
    texture.BindTexture();

    shader.SetUniform3fv("color", glm::vec3(1));
    shader.SetUniformFloat("time", glfwGetTime() / 2);

    glm::mat4 model = glm::mat4(1);
    model = glm::translate(model, translation);
    //std::cout << "Floor pos x:" << translation.x << "// Floor pos y: " << translation.y << "/Floor pos z: " << translation.z << std::endl;
    model = glm::scale(model, scale);

    shader.SetUniform3fv("viewPos", ContentManager::Cameras["main"]->CameraPos);
    shader.SetUniformMatrix4fv("model", model);
    shader.SetUniformMatrix4fv("projection", projection);
    shader.SetUniformMatrix4fv("view", view);

    shader.SetUniformInt("material.texture_diffuse1", 0);
    shader.SetUniformInt("material.texture_specular1", 1);
    shader.SetUniformFloat("material.shininess", 100.0f);

    for (int i = 0; i < 1; i++)
    {
        ContentManager::DirectionalLights[std::to_string(i)]->SetUniforms(shader);
    }


    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        ContentManager::PointLights[std::to_string(i)]->SetUniforms(shader);
    }


    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        ContentManager::SpotLights[std::to_string(i)]->SetUniforms(shader);
    }

    vao.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    vao.Unbind();
}


void Renderer::DrawInstances(int amount, Texture& texture, Texture& diffuseMap, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 color, Shader& shader)
{
    //Keep on draw:
    shader.Activate();

    diffuseMap.ActiveTextureUnit(0);
    diffuseMap.BindTexture();

    texture.ActiveTextureUnit(1);
    texture.BindTexture();

    shader.SetUniformFloat("material.shininess", 0.6);
    shader.SetUniformInt("material.texture_diffuse1", 0);
    shader.SetUniformInt("material.texture_specular1", 1);
    shader.SetUniformInt("hasTexture", 1);

    shader.SetUniform3fv("material.color", color);
    shader.SetUniform3fv("viewPos", ContentManager::Cameras["main"]->CameraPos);
    shader.SetUniformMatrix4fv("projection", projection);
    shader.SetUniformMatrix4fv("view", view);


    for (int i = 0; i < 1; i++)
    {
        ContentManager::DirectionalLights[std::to_string(i)]->SetUniforms(shader);
    }

    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        ContentManager::PointLights[std::to_string(i)]->SetUniforms(shader);
    }

    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        ContentManager::SpotLights[std::to_string(i)]->SetUniforms(shader);
    }

    vao.Bind();
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, amount);
    vao.Unbind();
}

void Renderer::DrawQuad2D(glm::vec3 scale, glm::vec3 color, Shader& shader, float screen_width, float screen_height)
{
    shader.Activate();
    shader.SetUniform3fv("color", color);
    glm::mat4 model = glm::mat4(1.f);
    glm::vec3 translation = glm::vec3(0.0, 0.0, 0.f);

    model = glm::translate(model, translation);
    model = glm::scale(model, scale);


    shader.SetUniformMatrix4fv("model", model);
    aimDotVao.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    aimDotVao.Unbind();
}

void Renderer::SetInstancedTranslations(int amount)
{
    instancesTranslationPtr = new glm::vec3[amount];


    srand(static_cast<unsigned int>(glfwGetTime())); // initialize random seed
    float radius = 1500.0;
    float offset = 250.0f;


    for (int i = 0; i < amount; i++)
    {
        float angle = (float)i / (float)amount * 360.0f;
        float displacement = (rand() % (int)(2 * offset * 100000)) / 10.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int)(2 * offset * 100000)) / 10.0f - offset;
        float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
        displacement = (rand() % (int)(2 * offset * 100000)) / 10.0f - offset;
        float z = cos(angle) * radius + displacement;
        glm::vec3 translation = glm::vec3(x,y,z);
        instancesTranslationPtr[i] = translation;
        std::cout << i << std::endl;
    }
}
