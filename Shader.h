#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<GLAD/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	GLuint Id;
	Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
	Shader();
	std::string alternative_get_file_content(const char* filename);
	void Activate();
	void Desativacte();
	void CheckShaderCompiling(GLuint shader, std::string type);
	void CheckProgramCompilinhg();
	void DeleteShader(GLuint shader);
	void SetUniformInt(const char* uniformName, GLint i);
	void SetUniformFloat(const char* uniformName, GLfloat f);
	void SetUniform3f(const char* uniformName, GLfloat x, GLfloat y, GLfloat z);
	void SetUniform3fv(const char* uniformName, glm::vec3 vec);
	void SetUniformMatrix4fv(const char* uniformName, glm::mat4 mat);
};

#endif
