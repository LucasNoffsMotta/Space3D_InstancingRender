#include "Mesh.h"
#include "Model.h"
#include "../Helper/ContentManager.h"

void Mesh::setupMesh()
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
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures, glm::vec3& color, float shininess)
{
	this->vertices = vertices;
	this->indices = indices;
	this->material = Material(textures, color, shininess);
	setupMesh();
}


void Mesh::Draw(Shader& shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;

	//1 = has texture
	//0 = none
	int hasTexture = material.textures.size() > 0 ? 1 : 0;
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

	shader.SetUniform3fv("material.color", material.color);
	shader.SetUniformFloat("material.shininess", material.shininess);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
