#include "Mesh.h"
#include "Model.h"

void Mesh::setupMesh()
{

	vao = VAO();
	vbo = VBO(&vertices[0], vertices.size() * sizeof(Vertex));
	ebo = EBO(&indices[0], indices.size() * sizeof(unsigned int));

	vao.Bind();
	vao.LinkAttrib(ebo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vao.LinkAttrib(ebo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	vao.LinkAttrib(ebo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	setupMesh();
}


void Mesh::Draw(Shader& shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		bool isDiffuse = textures[i].type == eTextureType::Diffuse;

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
		textures[i].BindTexture();
	}

	glActiveTexture(GL_TEXTURE0);
	vao.Bind();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	vao.Unbind();
}
