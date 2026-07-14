#include "Shader.h"
#include <string>

const std::string VERTEX_SHADER_ERROR = "Vertex Shader";
const std::string FRAGMENT_SHADER_ERROR = "Fragment Shader";
const std::string PROGRAM_ERROR = "Program";


std::string Shader::alternative_get_file_content(const char* filename)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string shaderCode;
	std::ifstream shaderFile;
	// ensure ifstream objects can throw exceptions:
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		shaderFile.open(filename);
		std::stringstream ShaderStream;
		// read file's buffer contents into streams
		ShaderStream << shaderFile.rdbuf();
		// close file handlers
		shaderFile.close();
		// convert stream into string
		shaderCode = ShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	return shaderCode;
}

Shader::Shader()
{

}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexShaderString = alternative_get_file_content(vertexFile);
	std::string fragmentShaderString = alternative_get_file_content(fragmentFile);

	const char* vertexShaderSource = vertexShaderString.c_str();
	const char* fragmentShaderSource = fragmentShaderString.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	CheckShaderCompiling(vertexShader, "V");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	CheckShaderCompiling(fragmentShader, "F");

	Id = glCreateProgram();
	glAttachShader(Id, vertexShader);
	glAttachShader(Id, fragmentShader);
	glLinkProgram(Id);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	CheckProgramCompilinhg();
}

void Shader::CheckProgramCompilinhg()
{
	int  success;
	char infoLog[512];
	glGetProgramiv(Id, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(Id, 512, NULL, infoLog);
		std::cout << "ERROR::" << PROGRAM_ERROR << "SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::Activate()
{
	glUseProgram(Id);
}

void Shader::Desativacte()
{
	glUseProgram(0);
}

void Shader::DeleteShader(GLuint shader)
{
	glDeleteShader(shader);
}

void Shader::CheckShaderCompiling(GLuint shader, std::string type)
{
	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success && type == "F")
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::" << "SHADER::" << FRAGMENT_SHADER_ERROR << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	else if (!success && type == "V")
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::" << "SHADER::" << VERTEX_SHADER_ERROR << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::SetUniform3f(const char* uniformName, GLfloat x, GLfloat y, GLfloat z)
{
	int uniformLocation = glGetUniformLocation(Id, uniformName);
	glUniform3f(uniformLocation, x, y, 0.0f);
}

void Shader::SetUniform3fv(const char* uniformName, glm::vec3 vec)
{
	int uniformLocation = glGetUniformLocation(Id, uniformName);
	glUniform3fv(uniformLocation, 1, glm::value_ptr(vec));
}

void Shader::SetUniformFloat(const char* uniformName, GLfloat f)
{
	int uniformLocation = glGetUniformLocation(Id, uniformName);
	glUniform1f(uniformLocation, f);
}

void Shader::SetUniformInt(const char* uniformName, GLint i)
{
	int uniformLocation = glGetUniformLocation(Id, uniformName);
	glUniform1i(uniformLocation, i);
}

void Shader::SetUniformMatrix4fv(const char* uniformName, glm::mat4 mat)
{
	int uniformLocation = glGetUniformLocation(Id, uniformName);
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mat));;
}