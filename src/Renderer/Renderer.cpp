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

void Renderer::CreatePointLights()
{
    glm::vec3 pos = glm::vec3(9, 0, 3);
    glm::vec3 color = glm::vec3(0.01);

    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        ContentManager::AddPointLight(i);
        ContentManager::PointLights[std::to_string(i)]->SetColor(color);
        ContentManager::PointLights[std::to_string(i)]->SetPosition(pos);
        pos.x -= 100;
        color.x -= 0.1;
    }
}

void Renderer::CreateSpotLights()
{
    glm::vec3 pos = glm::vec3(10, -1000, 0);
    glm::vec3 direction = glm::vec3(0, -1, 0);
    glm::vec3 color = glm::vec3(0.3, 0, 0.3);

    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        ContentManager::AddSpotLight(i);
        ContentManager::SpotLights[std::to_string(i)]->SetColor(color);
        ContentManager::SpotLights[std::to_string(i)]->SetPosition(pos);
        ContentManager::SpotLights[std::to_string(i)]->SetDirection(direction);
        pos.x -= 30;
        color.z -= 0.1;
    }
}

void Renderer::CreateDirectionalLights()
{
    glm::vec3 direction = glm::vec3(-0.2f, -1.0f, -0.3f);
    glm::vec3 ambient =  glm::vec3(0.05f, 0.05f, 0.05f);
    glm::vec3 diff = glm::vec3(0.4f, 0.4f, 0.4f);
    glm::vec3 spec = glm::vec3(0.5f, 0.5f, 0.5f);

    for (int i = 0; i < 1; i++)
    {
        ContentManager::AddDirectionalLight(i);
        ContentManager::DirectionalLights[std::to_string(i)]->SetDirection(direction);
        ContentManager::DirectionalLights[std::to_string(i)]->SetSpecular(spec);
        ContentManager::DirectionalLights[std::to_string(i)]->SetDiffuse(diff);
        ContentManager::DirectionalLights[std::to_string(i)]->SetAmbient(ambient);
    }
}

void Renderer::SetSceneLightUniforms(Shader& shader)
{
    //Set scene lights uniforms:
    for (int i = 0; i < 1; i++)
    {
        ContentManager::DirectionalLights[std::to_string(i)]->SetUniforms(shader);
    }

    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        ContentManager::PointLights[std::to_string(i)]->SetUniforms(shader);
    }

    //Ugly!
    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        if (i == 0)
        {
            if (ContentManager::Cameras["main"]->cameraLight == 1)
            {
                ContentManager::SpotLights[std::to_string(i)]->SetPosition(ContentManager::Cameras["main"]->CameraPos);
                ContentManager::SpotLights[std::to_string(i)]->SetDirection(ContentManager::Cameras["main"]->CameraFront);
                ContentManager::SpotLights[std::to_string(i)]->SetUniforms(shader);
                continue;
            }

            else
            {
                glm::vec3 zeroVec = glm::vec3(0);
                ContentManager::SpotLights[std::to_string(i)]->SetAmbient(zeroVec);
                continue;
            }
        }

        ContentManager::SpotLights[std::to_string(i)]->SetUniforms(shader);
    }
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

void Renderer::DrawScene(Shader& shader, Shader& stencilShader, Shader& boundBoxShader)
{
    shader.Activate();
    shader.SetUniformMatrix4fv("projection", projection);
    shader.SetUniformMatrix4fv("view", view);
    SetSceneLightUniforms(shader);

    //here i am rendering first an object that cannot be outlined.
    // What if ALL objects can be outlined? 
    //The gorund rule for this to work is: the ground / terrain cannot be outlined! Only objects above it.
  
    //Draw Terrain - No Stencil Test
    glStencilMask(0x00);

    for (int i = 0; i < ContentManager::Models["terrain"].size(); i++)
    {
        Model* terrain = ContentManager::Models["terrain"].at(i);

        glm::mat4 model_matrix = glm::mat4(1.0f);
        model_matrix = glm::translate(model_matrix, terrain->GetWorldPosition());

        if (terrain->rotationAngle > 0) {
            model_matrix = glm::rotate(model_matrix, glm::radians(terrain->rotationAngle), terrain->rotationAxis);
        }

        model_matrix = glm::scale(model_matrix, terrain->GetScale());
        shader.SetUniformMatrix4fv("model", model_matrix);
        terrain->Draw(shader);
    }

    //Stencil Activated
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);

    for (int i = 0; i < ContentManager::Models["object"].size(); i++)
    {
        Model* obj = ContentManager::Models["object"].at(i);

        glm::mat4 model_matrix = glm::mat4(1.0f);
        model_matrix = glm::translate(model_matrix, obj->GetWorldPosition());

        if (obj->rotationAngle > 0) {
            model_matrix = glm::rotate(model_matrix, glm::radians(obj->rotationAngle), obj->rotationAxis);
        }

        model_matrix = glm::scale(model_matrix, obj->GetScale());
        shader.SetUniformMatrix4fv("model", model_matrix);
        obj->Draw(shader);
    }
    
    //Second Pass: Draw Outline - If outlined objects exists
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);

    stencilShader.Activate();
    stencilShader.SetUniformMatrix4fv("projection", projection);
    stencilShader.SetUniformMatrix4fv("view", view);

    for (int i = 0; i < ContentManager::Models["object"].size(); i++)
    {
        Model* obj = ContentManager::Models["object"].at(i);

        if (obj->outline)
        {
            glm::mat4 scaled = glm::mat4(1);
            scaled = glm::translate(scaled, obj->GetWorldPosition());

            if (obj->rotationAngle > 0) {
                scaled = glm::rotate(scaled, glm::radians(obj->rotationAngle), obj->rotationAxis);
            }

            scaled = glm::scale(scaled, obj->GetScale() * glm::vec3(1.01));
            stencilShader.SetUniformMatrix4fv("model", scaled);
            obj->Draw(stencilShader);
        }
    }

    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glEnable(GL_DEPTH_TEST);

    //Third pass: Render bound box!
    for (int i = 0; i < ContentManager::Models["object"].size(); i++)
    {
        Model* obj = ContentManager::Models["object"].at(i);
        DrawBoundBox(boundBoxShader, *obj);
    }
}

void Renderer::DrawBoundBox(Shader& shader, Model& boundModel)
{
    shader.Activate();
    shader.SetUniformMatrix4fv("projection", projection);
    shader.SetUniformMatrix4fv("view", view);

    glm::mat4 model = glm::mat4(1);
    model = glm::translate(model, boundModel.GetWorldPosition());

    if (boundModel.rotationAngle > 0)
    {
        model = glm::rotate(model, glm::radians(boundModel.rotationAngle), boundModel.rotationAxis);
    }

    model = glm::scale(model, glm::vec3(4, 0.1, 3));

    shader.SetUniformMatrix4fv("model", model);


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    vao.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    vao.Unbind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
