#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<GLFW/glfw3.h>
#include<GLAD/glad.h>

class Mesh;

class VBO
{
public:
	GLuint Id;
	VBO();
	VBO(const void* vertices, GLsizeiptr size);
	void Bind();
	void Unbind();
	void Delete();
};

#endif
