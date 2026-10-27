#pragma once
#include <string>

class Shader
{

public:

	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	~Shader();

	void Use() const;

private:

	std::string ReadFileToString(const char* filePath);
	void CheckCompileErrors(unsigned int shaderID, std::string type);

};