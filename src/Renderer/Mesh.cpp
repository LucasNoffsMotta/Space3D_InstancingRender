#include "Mesh.h"
#include "Model.h"
#include "../Helper/ContentManager.h"

void Mesh::setupMesh(int layouts)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
		&indices[0], GL_STATIC_DRAW);


	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	if (layouts == 1)
	{
		glBindVertexArray(0);
		return;
	}

	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	if (layouts == 2)
	{
		glBindVertexArray(0);
		return;
	}

	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	if (layouts == 3)
	{
		glBindVertexArray(0);
		return;
	}
}

int Mesh::GetVAO()
{
	return VAO;
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures, glm::vec4& color, float shininess, float ior, int layouts)
{
	this->vertices = vertices;
	this->indices = indices;
	this->material = Material(textures, color, shininess, ior);
	setupMesh(layouts);
}


void Mesh::Draw(Shader& shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;

	//1 = has texture
	//0 = none
	int hasTexture = material.textures.size() > 0 ? 1 : 0;
	int hasReflection = 0;
	shader.Activate();
	shader.SetUniformInt("hasTexture", hasTexture);
	shader.SetUniformInt("material.useColor", 1); //Use color by default


	for (unsigned int i = 0; i < material.textures.size(); i++)
	{
		material.textures[i].ActiveTextureUnit(i);
		material.textures[i].BindTexture();
		shader.SetUniformInt("material.useColor", 0); //USE TEXTURE IF HAS TEXTURE!

		std::string number;
		std::string name = material.textures[i].TextureTypeToUniform(material.textures[i].type);

		if (material.textures[i].type == eTextureType::Diffuse)
		{
			number = std::to_string(diffuseNr++);
		}

		else if (material.textures[i].type == eTextureType::Specular)
		{
			number = std::to_string(specularNr++);
		}

		else if (material.textures[i].type == eTextureType::Diffuse_CubeMap)
		{
			shader.SetUniformInt(("material." + name).c_str(), i);
			hasReflection = 1;

			//If mesh has only 1 texture, and it is the skybox texture, the shader will use mtl color to calculate frag color
			//Otherwise, can use the diffuse
			if (material.textures.size() == 1)
			{
				shader.SetUniformInt("material.useColor", 1); //USE COLOR IF THE ONLY TEXTURE IS FOR REFLECTION (IT WILL MIX THE COLOR AND REFLECTION INSIDE THE SHADER)!
			}

			continue;
		}

		shader.SetUniformInt(("material." + name + number).c_str(), i);
	}

	shader.SetUniformInt("HasReflectionTexture", hasReflection);
	shader.SetUniform4fv("material.color", material.color);
	shader.SetUniformFloat("material.ior", 0.5f); 	// material.IndiceOfReflection
	shader.SetUniformFloat("material.shininess", material.shininess);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);


	//Very important: Had a anoying bug with textures not being rendered due to that. It is important to reset the shader uniform flag to default after changing it inside a conditional clausule. 
	//The objects share the same shader program, so if a shader uniform flag is changed between frames, the next object can receive a "dirt" shader
	shader.SetUniformInt("HasReflectionTexture", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::DrawInstanced(Shader& shader, int amount)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;

	//1 = has texture
	//0 = none
	int hasTexture = material.textures.size() > 0 ? 1 : 0;
	shader.Activate();
	shader.SetUniformInt("hasTexture", hasTexture);

	for (unsigned int i = 0; i < material.textures.size(); i++)
	{
		material.textures[i].ActiveTextureUnit(i);
		material.textures[i].BindTexture();

		bool isDiffuse = material.textures[i].type == eTextureType::Diffuse;

		std::string number;
		std::string name = isDiffuse ? "texture_diffuse" : "texture_specular";

		if (isDiffuse)
		{
			number = std::to_string(diffuseNr++);
		}

		else
		{
			number = std::to_string(specularNr++);
		}

		shader.SetUniformInt(("material." + name + number).c_str(), i);
	}

	shader.SetUniform4fv("material.color", material.color);
	shader.SetUniformFloat("material.shininess", material.shininess);

	glBindVertexArray(VAO);
	glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0, amount);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
