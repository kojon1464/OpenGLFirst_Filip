#pragma once

#include <glad\glad.h>
#include <iostream>
#include <fstream>
#include <string>
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);

	void use();

	void setUniformBool(const char* name, bool value);
	void setUniformFloat(const char* name, float value);
	void setUniformInt(const char* name, int value);
	void setUniformMatrix4(const char* name, glm::mat4 trans);

	virtual ~Shader();
private:
	unsigned int m_shaderProgram;
};

