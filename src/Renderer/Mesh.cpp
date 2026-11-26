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

///TODO: Ongoing -> REFACTORING THIS
void Mesh::Draw(Shader& shader, bool useInstanced, int instancedAmmount)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;


	//Count number of textures used, so then it will be possible to properly clean the shader program:
	int totalActiveTextureUnits = 0;


	shader.Activate();
	shader.SetUniformInt("hasTexture", this->material.hasTexture);
	shader.SetUniformInt("material.useColor", this->material.useColor);
	shader.SetUniformInt("HasReflectionTexture", this->material.hasReflection);
	shader.SetUniform4fv("material.color", material.color);
	shader.SetUniformFloat("material.ior", 0.5f); 	// material.IndiceOfReflection
	shader.SetUniformFloat("material.shininess", material.shininess);


	for (unsigned int i = 0; i < material.textures.size(); i++)
	{
		material.textures[i].ActiveTextureUnit(i);
		totalActiveTextureUnits++;

		material.textures[i].BindTexture();
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
			continue;
		}

		shader.SetUniformInt(("material." + name + number).c_str(), i);
	}

	glBindVertexArray(VAO);

	if (useInstanced)
	{
		glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0, instancedAmmount);
	}

	else
	{
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);

	//Very important: Had a anoying bug with textures not being rendered due to that. It is important to reset the shader uniform flag to default after changing it inside a conditional clausule. 
	//The objects share the same shader program, so if a shader uniform flag is changed between frames, the next object can receive a "dirt" shader

	//RESET ALL CONFIG TO DEFAULT (CLEAN THE SHADER PROGRAM)
	shader.SetUniformInt("HasReflectionTexture", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);


	////This code is being called a lot of times on random moments
	//for (int i = 0; i < totalActiveTextureUnits; i++)
	//{
	//	glActiveTexture(GL_TEXTURE0 + i);
	//	glBindTexture(GL_TEXTURE_2D, 0);
	//}
}
