#pragma once

#include <glad\glad.h>
#include <iostream>
#include <fstream>
#include <string>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);

	void use();

	virtual ~Shader();
private:
	unsigned int shaderProgram;
};

