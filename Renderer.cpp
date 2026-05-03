#include "Renderer.h"
#include "VAO.h"


void Renderer::InitRenderData()
{
    float square[] = {
             -0.5f, -0.5f, -0.5f, 0.2, 0.1, 0.2,
             0.5f, -0.5f, -0.5f, 0.4, 1.0, 1.0,
             0.5f,  0.5f, -0.5f, 1.0, 0.3, 0.2,
             0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0,
            -0.5f,  0.5f, -0.5f, 0.0, 0.0, 1.0,
            -0.5f, -0.5f, -0.5f, 1.0, 1.0, 0.4,

            -0.5f, -0.5f,  0.5f, 0.2, 0.1, 0.2,
             0.5f, -0.5f,  0.5f, 0.2, 0.1, 0.2,
             0.5f,  0.5f,  0.5f, 0.2, 0.1, 0.2,
             0.5f,  0.5f,  0.5f, 0.2, 0.1, 0.2,
            -0.5f,  0.5f,  0.5f, 0.2, 0.1, 0.2,
            -0.5f, -0.5f,  0.5f, 0.2, 0.1, 0.2,

            -0.5f,  0.5f,  0.5f, 1.0, 0.3, 0.2,
            -0.5f,  0.5f, -0.5f, 1.0, 0.3, 0.2,
            -0.5f, -0.5f, -0.5f, 1.0, 0.3, 0.2,
            -0.5f, -0.5f, -0.5f, 0.2, 0.1, 0.2,
            -0.5f, -0.5f,  0.5f, 0.2, 0.1, 0.2,
            -0.5f,  0.5f,  0.5f, 0.2, 0.1, 0.2,

             0.5f,  0.5f,  0.5f, 0.4, 1.0, 1.0,
             0.5f,  0.5f, -0.5f, 0.4, 1.0, 1.0,
             0.5f, -0.5f, -0.5f, 0.0, 0.0, 1.0,
             0.5f, -0.5f, -0.5f, 0.4, 1.0, 1.0,
             0.5f, -0.5f,  0.5f, 1.0, 1.0, 0.4,
             0.5f,  0.5f,  0.5f, 1.0, 0.3, 0.2,

            -0.5f, -0.5f, -0.5f, 0.4, 1.0, 1.0,
             0.5f, -0.5f, -0.5f, 0.4, 1.0, 1.0,
             0.5f, -0.5f,  0.5f, 1.0, 0.3, 0.2,
             0.5f, -0.5f,  0.5f, 0.4, 1.0, 1.0,
            -0.5f, -0.5f,  0.5f, 1.0, 1.0, 0.4,
            -0.5f, -0.5f, -0.5f, 1.0, 0.3, 0.2,

            -0.5f,  0.5f, -0.5f, 1.0, 0.3, 0.2,
             0.5f,  0.5f, -0.5f, 0.4, 1.0, 1.0,
             0.5f,  0.5f,  0.5f, 0.4, 1.0, 1.0,
             0.5f,  0.5f,  0.5f, 1.0, 0.3, 0.2,
            -0.5f,  0.5f,  0.5f, 0.4, 1.0, 1.0,
            -0.5f,  0.5f, -0.5f, 0.4, 1.0, 1.0,
    };

    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)1300 / 1200, 0.1f, 10000000.f);

    vao = VAO();
    VBO vbo = VBO(square, sizeof(square));
    vao.Bind();
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(float) * 6, (void*)0);
    vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(float) * 6, (void*)(3 * sizeof(float)));
}

Renderer::Renderer()
{
    InitRenderData();
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



void Renderer::Draw(glm::vec3 translation, glm::vec3 scale, glm::vec3 rotation, float rotationAngle, glm::vec3 color, Shader& shader)
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

    vao.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    vao.Unbind();
}

void Renderer::DrawInstances(glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 color, Shader& shader)
{
    shader.Activate();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, rotationAngle, glm::vec3(rotationAxis.x, rotationAxis.y, rotationAxis.z));
    model = glm::scale(model, scale);
    glm::vec3* ptrDummy = instancesTranslationPtr;

    for (int i = 0; i < 100; i++)
    {
        glm::vec3 trans = *ptrDummy;
        std::string uniform = "offsets[" + std::to_string(i) + "]";
        shader.SetUniform3fv(("offsets[" + std::to_string(i) + "]").c_str(), trans);
        ptrDummy++;
    }

    shader.SetUniform3fv("color", color);
    shader.SetUniformFloat("time", glfwGetTime() / 2);
    shader.SetUniformMatrix4fv("model", model);
    shader.SetUniformMatrix4fv("projection", projection);
    shader.SetUniformMatrix4fv("view", view);

    vao.Bind();
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 100);
    vao.Unbind();
}

void Renderer::DrawInstances(int amount, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 color, Shader& shader)
{
    //Keep on draw:
    shader.Activate();

    shader.SetUniform3fv("color", color);
    shader.SetUniformFloat("time", glfwGetTime() / 2);
    shader.SetUniformMatrix4fv("projection", projection);
    shader.SetUniformMatrix4fv("view", view);

    vao.Bind();
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, amount);
    vao.Unbind();
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
    }
}
