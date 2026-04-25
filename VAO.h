#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<GLAD/glad.h>
#include<GLFW/glfw3.h>
#include "VBO.h"

class VAO
{
public:
	VAO();
	GLuint Id;
	void Bind();
	void Unbind();
	void LinkAttrib(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
};

#endif
