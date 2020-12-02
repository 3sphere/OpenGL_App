#include <glad/glad.h>
#include "Shader.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <utility>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) :
	id(0)
{
	std::ifstream vertexFile(vertexPath);
	std::ifstream fragmentFile(fragmentPath);
	if (!vertexFile) 
	{
		std::cout << "Failed to read shader at " << vertexPath << std::endl;
	}
	if (!fragmentFile)
	{
		std::cout << "Failed to read shader at " << fragmentPath << std::endl;
	}

	std::string vertexCode = readFromFile(vertexPath);
	std::string fragmentCode = readFromFile(fragmentPath);

	const char *vertexCodeCstr = vertexCode.c_str();
	const char *fragmentCodeCstr = fragmentCode.c_str();

	unsigned int vertexShader = compileShader(VERTEX, vertexCodeCstr);
	unsigned int fragmentShader = compileShader(FRAGMENT, fragmentCodeCstr);

	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);

	int success;
	char infoLog[512];
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id, 512, nullptr, infoLog);
		std::cout << "Failed to link shader program\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use()
{
	glUseProgram(id);
}

void Shader::setInt(const std::string& uniformName, int value)
{
	glUniform1i(glGetUniformLocation(id, uniformName.c_str()), value);
}

void Shader::setBool(const std::string& uniformName, bool value)
{
	glUniform1i(glGetUniformLocation(id, uniformName.c_str()), value);
}

void Shader::setFloat(const std::string& uniformName, float value)
{
	glUniform1f(glGetUniformLocation(id, uniformName.c_str()), value);
}

void Shader::setVec2f(const std::string& uniformName, float v0, float v1)
{
	glUniform2f(glGetUniformLocation(id, uniformName.c_str()), v0, v1);
}

void Shader::setVec3f(const std::string& uniformName, float v0, float v1, float v2)
{
	glUniform3f(glGetUniformLocation(id, uniformName.c_str()), v0, v1, v2);
}

void Shader::setVec4f(const std::string& uniformName, float v0, float v1, float v2, float v3)
{
	glUniform4f(glGetUniformLocation(id, uniformName.c_str()), v0, v1, v2, v3);
}

void Shader::setMat4f(const std::string& uniformName, const glm::mat4& mat)
{
	glUniformMatrix4fv(glGetUniformLocation(id, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

unsigned int Shader::compileShader(Type type, const char* src)
{
	unsigned int id;
	GLenum shaderType;
	if (type == VERTEX)
	{
		shaderType = GL_VERTEX_SHADER;
	}
	else if (type == FRAGMENT) 
	{
		shaderType = GL_FRAGMENT_SHADER;
	}
	else
	{
		return 0;
	}
		
	id = glCreateShader(shaderType);
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int success;
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		glGetShaderInfoLog(id, 512, nullptr, infoLog);
		std::cout << "Failed to compile shader\n" << infoLog << std::endl;
		return 0;
	}

	return id;
}

std::string Shader::readFromFile(const std::string& filePath)
{
	std::ifstream file(filePath);
	if (!file)
	{
		std::cout << "Failed to read shader at " << filePath << std::endl;
	}

	std::string shaderCode;
	std::string temp;
	while (std::getline(file, temp))
	{
		shaderCode += temp;
		shaderCode += '\n';
	}

	return shaderCode;
}


