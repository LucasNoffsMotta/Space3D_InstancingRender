#include "Render/Renderer.h"
#include "Render/VAO.h"
#include <Helper/ContentManager.h>



void Renderer::InitRenderData()
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


    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)1300 / 1200, 0.1f, 10000000.f);

    vao = VAO();
    VBO vbo = VBO(square, sizeof(square));
    vao.Bind();
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(float) * 11, (void*)0);
    vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(float) * 11, (void*)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 3, 3, GL_FLOAT, sizeof(float) * 11, (void*)(6 * sizeof(float)));
    vao.LinkAttrib(vbo, 4, 2, GL_FLOAT, sizeof(float) * 11, (void*)(9 * sizeof(float)));
}

void Renderer::InitAimDotRenderData()
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

void Renderer::InitBulletRenderData()
{
    float square[] = {
           -0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0,
            0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0,
            0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0,
            0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0,
           -0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0,
           -0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0,

           -0.5f, -0.5f,  0.5f, 1.0, 1.0, 1.0,
            0.5f, -0.5f,  0.5f, 1.0, 0.1, 1.0,
            0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0,
            0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0,
           -0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0,
           -0.5f, -0.5f,  0.5f, 1.0, 1.0, 1.0,

           -0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0,
           -0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0,
           -0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0,
           -0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0,
           -0.5f, -0.5f,  0.5f, 1.0, 1.0, 1.0,
           -0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0,

            0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0,
            0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0,
            0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0,
            0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0,
            0.5f, -0.5f,  0.5f, 1.0, 1.0, 1.0,
            0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0,

           -0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0,
            0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0,
            0.5f, -0.5f,  0.5f, 1.0, 1.0, 1.0,
            0.5f, -0.5f,  0.5f, 1.0, 1.0, 1.0,
           -0.5f, -0.5f,  0.5f, 1.0, 1.0, 1.0,
           -0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0,

           -0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0,
            0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0,
            0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0,
            0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0,
           -0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0,
           -0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0,
    };

    bulletVao = VAO();
    VBO vbo = VBO(square, sizeof(square));
    bulletVao.Bind();
    bulletVao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(float) * 6, (void*)0);
    bulletVao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(float) * 6, (void*)(3 * sizeof(float)));
}

Renderer::Renderer()
{
    InitRenderData();
    CreatePointLights();
}

void Renderer::SetActiveShader(Shader& shader)
{
    shader.Activate();
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

glm::vec3 Renderer::GetTranslationPos(int index)
{
    glm::vec3 pos;
    pos.x = modelMatrices[index][3].x;
    pos.y = modelMatrices[index][3].y;
    pos.z = modelMatrices[index][3].z;
    return pos;
}



void Renderer::CreatePointLights()
{
    glm::vec3 pos = glm::vec3(0, 10, 0);

    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        ContentManager::AddPointLight(i);
        ContentManager::PointLights[std::to_string(i)]->SetPosition(pos);
        pos.x += 30;
    }
}

void Renderer::Draw(glm::vec3 translation, Texture& texture, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 color, Shader& shader)
{
    //Keep on draw:
    shader.Activate();
    texture.BindTexture();

    glm::vec3 pos1 = glm::vec3(0, 10, 0);

    glm::vec3 pos2 = glm::vec3(10, 10, -10);

    glm::vec3 pos3 = glm::vec3(50, 10, -10);

    glm::vec3 pos4 = glm::vec3(80, 10, -5);

    shader.SetUniform3fv("color", glm::vec3(1));
    shader.SetUniformFloat("time", glfwGetTime() / 2);

    glm::mat4 model = glm::mat4(1);
    model = glm::translate(model, translation);
    model = glm::scale(model, scale);

    shader.SetUniform3fv("viewPos", ContentManager::Cameras["main"]->CameraPos);
    shader.SetUniformMatrix4fv("model", model);
    shader.SetUniformMatrix4fv("projection", projection);
    shader.SetUniformMatrix4fv("view", view);

    shader.SetUniformInt("material.diffuse", 0);
    shader.SetUniformInt("material.specular", 1);
    shader.SetUniformFloat("material.shininess", 100.0f);

    shader.SetUniform3fv("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
    shader.SetUniform3fv("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
    shader.SetUniform3fv("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
    shader.SetUniform3fv("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    shader.SetUniform3fv("dirLight.color", glm::vec3(0.01f, 0.01f, 0.01f));


    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        ContentManager::PointLights[std::to_string(i)]->SetUniforms(shader);
    }

    shader.SetUniform3fv("spotLight.position", ContentManager::Cameras["main"]->CameraPos);
    shader.SetUniform3fv("spotLight.color", glm::vec3(1.0, 1.0, 0.0));
    shader.SetUniform3fv("spotLight.direction", ContentManager::Cameras["main"]->CameraFront);
    shader.SetUniform3fv("spotLight.ambient", glm::vec3(0.0f, 0.0f, 1.0f));
    shader.SetUniform3fv("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
    shader.SetUniform3fv("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    shader.SetUniformFloat("spotLight.constant", 1.0f);
    shader.SetUniformFloat("spotLight.linear", 0.0014);
    shader.SetUniformFloat("spotLight.quadratic", 0.000007);
    shader.SetUniformFloat("spotLight.innerCutoff", glm::cos(glm::radians(9.5f)));
    shader.SetUniformFloat("spotLight.outerCutoff", glm::cos(glm::radians(25.0f)));

    vao.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    vao.Unbind();
}

void Renderer::DrawBullet(glm::vec3 translation, glm::vec3 scale, glm::vec3 rotation, float rotationAngle, glm::vec3 color, Shader& shader)
{
    shader.Activate();

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, translation);
    model = glm::rotate(model, rotationAngle, glm::vec3(rotation.x, rotation.y, rotation.z));
    model = glm::scale(model, scale);

    shader.SetUniform3fv("color", color);
    shader.SetUniformFloat("time", glfwGetTime() / 2);
    shader.SetUniformMatrix4fv("model", model);
    shader.SetUniformMatrix4fv("projection", projection);
    shader.SetUniformMatrix4fv("view", view);

    bulletVao.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    bulletVao.Unbind();
}

void Renderer::DrawInstances(int amount, Texture& texture, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 color, Shader& shader)
{
    //Keep on draw:
    shader.Activate();
    texture.BindTexture();
    shader.SetUniformFloat("material.shininess", 40.0f);
    shader.SetUniformInt("material.diffuse", 0);
    shader.SetUniformInt("material.specular", 1);

    shader.SetUniform3fv("color", color);
    shader.SetUniformFloat("time", glfwGetTime() / 2);
    shader.SetUniform3fv("viewPos", ContentManager::Cameras["main"]->CameraPos);
    shader.SetUniformMatrix4fv("projection", projection);
    shader.SetUniformMatrix4fv("view", view);


    shader.SetUniform3fv("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
    shader.SetUniform3fv("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
    shader.SetUniform3fv("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
    shader.SetUniform3fv("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    shader.SetUniform3fv("dirLight.color", glm::vec3(0.01f, 0.01f, 0.01f));

    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        ContentManager::PointLights[std::to_string(i)]->SetUniforms(shader);
    }

    shader.SetUniform3fv("spotLight.position", ContentManager::Cameras["main"]->CameraPos);
    shader.SetUniform3fv("spotLight.color", glm::vec3(1.0, 1.0, 0.0));
    shader.SetUniform3fv("spotLight.direction", ContentManager::Cameras["main"]->CameraFront);
    shader.SetUniform3fv("spotLight.ambient", glm::vec3(0.0f, 0.0f, 1.0f));
    shader.SetUniform3fv("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
    shader.SetUniform3fv("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    shader.SetUniformFloat("spotLight.constant", 1.0f);
    shader.SetUniformFloat("spotLight.linear", 0.0014);
    shader.SetUniformFloat("spotLight.quadratic", 0.000007);
    shader.SetUniformFloat("spotLight.innerCutoff", glm::cos(glm::radians(9.5f)));
    shader.SetUniformFloat("spotLight.outerCutoff", glm::cos(glm::radians(25.0f)));

    vao.Bind();
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, amount);
    vao.Unbind();
}

void Renderer::DrawAimDot(glm::vec3 scale, glm::vec3 color, Shader& shader, float screen_width, float screen_height)
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
