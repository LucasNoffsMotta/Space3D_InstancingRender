#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<GLAD/glad.h>
#include<GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include "Render/VBO.h"
#include <glm/ext/matrix_float4x4.hpp>

class VAO
{
public:
	VAO();
	GLuint Id;
	void Bind();
	void Unbind();
	void LinkAttrib(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void LinkInstancedMat4(glm::mat4* modelMatrices, int amount);
};

#endif
