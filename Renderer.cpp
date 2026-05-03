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
    projection = glm::perspective(glm::radians(45.0f), (float)1300 / 1200, 0.1f, 1000.f);

    vao = VAO();
    VBO vbo = VBO(square, sizeof(square));
    vao.Bind();
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(float) * 6, (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(float) * 6, (void*)(3 * sizeof(float)));
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
    modelMatrices = new glm::mat4[ammount*ammount];

    for (int i = 0; i < ammount* ammount; i++)
    {
        glm::vec3 trans = *translations;
        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model, trans);
        modelMatrices[i] = model;
        translations++;
    }
}

void Renderer::SetInstancesBuffers(int amount)
{
    //glm::vec3* translations = SetInstancedTranslations(amount);
    //SetModelMatrices(translations, amount);
    //vao.LinkInstancedMat4(modelMatrices, amount);
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
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, amount * amount);
    vao.Unbind();
}

void Renderer::SetInstancedTranslations(int amount)
{
    instancesTranslationPtr = new glm::vec3[100];

    int index = 0;
    float offset = 0.1f;

    for (int x = -10; x < 10; x+=2)
    {
        for (int z = -10; z < 10; z+=2)
        {
            glm::vec3 translation;
            translation.x = (float)x / 10.0f + offset;
            translation.y = 0.f;
            translation.z = (float)z / 10.0f + offset;
            instancesTranslationPtr[index++] = translation;
            std::cout << index << std::endl;
        }
    }
}
