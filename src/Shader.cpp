#include "Shader.hpp"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{

	std::string vertexCode = ReadFileToString(vertexPath);
	std::string fragmentCode = ReadFileToString(fragmentPath);

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);
	CheckCompileErrors(vertexShader, "VERTEX");

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
	CheckCompileErrors(fragmentShader, "FRAGMENT");

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	CheckCompileErrors(ID, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

Shader::~Shader()
{

	glDeleteProgram(ID);

}

void Shader::Use() const
{

	glUseProgram(ID);

}

std::string Shader::ReadFileToString(const char* filePath)
{

	std::ifstream file;
	std::stringstream stream;

	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{

		file.open(filePath);
		stream << file.rdbuf();
		file.close();

	}
	catch (std::ifstream::failure& e)
	{

		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << filePath << std::endl;

	}

	return stream.str();

}

void Shader::CheckCompileErrors(unsigned int shaderID, std::string type)
{

	int success;
	char infoLog[1024];

	if (type != "PROGRAM")
	{

		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{

			glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
			std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- \n";

		}

	}
	else
	{

		glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
		if (!success)
		{

			glGetProgramInfoLog(shaderID, 1024, NULL, infoLog);
			std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- \n";

		}

	}
}