#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<GLAD/glad.h>

class EBO
{
public:
	GLuint ID;
	EBO();
	EBO(GLuint* indices, GLsizeiptr size);
	void Bind();
	void Unbind();
	void Delete();
};


#endif#pragma once

