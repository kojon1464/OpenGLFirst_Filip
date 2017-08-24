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

	void setUniformBool(const char* name, bool value);
	void setUniformFloat(const char* name, float value);
	void setUniformInt(const char* name, int value);

	virtual ~Shader();
private:
	unsigned int shaderProgram;
};

