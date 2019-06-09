#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "Shader.h"


Shader::Shader(const char *pVertexFilePath, const char *pFragmentFilePath, const char *pGeometryFilePath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertexFileStream;
	std::ifstream fragmentFileStream;
	vertexFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		//open : file --> ifstream
		vertexFileStream.open(pVertexFilePath);
		fragmentFileStream.open(pFragmentFilePath);

		std::stringstream vertexStringStream;
		std::stringstream fragmentStringStream;

		//ifstream.rdbuf() --> stringstream
		vertexStringStream << vertexFileStream.rdbuf();
		fragmentStringStream << fragmentFileStream.rdbuf();

		//ifstream.close()
		vertexFileStream.close();
		fragmentFileStream.close();

		//stringstream.str() --> string
		vertexCode = vertexStringStream.str();
		fragmentCode = fragmentStringStream.str();

	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ, reason : " << e.what() << std::endl;
	}

	//string -- > char *
	const char *vertexContents = vertexCode.c_str();
	const char *fragmentContents = fragmentCode.c_str();
		
	unsigned int vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexContents, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, COMPILE);

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentContents, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, COMPILE);

	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertex);
	glAttachShader(shaderID, fragment);
	glLinkProgram(shaderID);
	checkCompileErrors(shaderID, LINK);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void Shader::checkCompileErrors(GLuint shader, CompileType pCompileType)
{
	GLint success;
	GLchar infoLog[1024];
	if (pCompileType == COMPILE)
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << pCompileType << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else if (pCompileType == LINK)
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << pCompileType << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}


