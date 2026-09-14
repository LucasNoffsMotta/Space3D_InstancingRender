#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<GLFW/glfw3.h>
#include<GLAD/glad.h>

class VBO
{
public:
	GLuint Id;
	VBO();
	VBO(GLfloat* vertices, GLsizeiptr size);
	void Bind();
	void Unbind();
	void Delete();
};

#endif
