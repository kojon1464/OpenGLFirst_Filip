#include "shader.h"

static std::string loadSorceCodeFromFile(const char* path);

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexShaderCode, fragmentShaderCode;

	vertexShaderCode = loadSorceCodeFromFile(vertexPath);
	fragmentShaderCode = loadSorceCodeFromFile(fragmentPath);

	const char* vertexShaderSorce = vertexShaderCode.c_str();
	const char* fragmentShaderSorce = fragmentShaderCode.c_str();

	unsigned int vertexShader, fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSorce, NULL);
	glCompileShader(vertexShader);

	int sucess;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &sucess);
	if (!sucess)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "Vertex shader compilation failed\n" << infoLog << std::endl;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSorce, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &sucess);
	if (!sucess)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "Fragment shader compilation failed\n" << infoLog << std::endl;
	}

	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, vertexShader);
	glAttachShader(m_shaderProgram, fragmentShader);
	glLinkProgram(m_shaderProgram);

	glGetProgramiv(m_shaderProgram, GL_COMPILE_STATUS, &sucess);
	if (!sucess)
	{
		glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
		std::cerr << "Program failed to link shaders\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use() 
{
	glUseProgram(m_shaderProgram);
}

void Shader::setUniformBool(const char* name, bool value)
{
	glUseProgram(m_shaderProgram);
	glUniform1i(glGetUniformLocation(m_shaderProgram, name), (int)value);
}

void Shader::setUniformFloat(const char* name, float value)
{
	glUseProgram(m_shaderProgram);
	glUniform1f(glGetUniformLocation(m_shaderProgram, name), value);
}

void Shader::setUniformInt(const char* name, int value)
{
	glUseProgram(m_shaderProgram);
	glUniform1i(glGetUniformLocation(m_shaderProgram, name), value);
}

void Shader::setUniformMatrix4(const char* name, glm::mat4 trans)
{
	glUseProgram(m_shaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, name), 1, GL_FALSE, glm::value_ptr(trans));
}

Shader::~Shader()
{
	glDeleteProgram(m_shaderProgram);
}

std::string loadSorceCodeFromFile(const char* path)
{
	std::string code, line;
	std::fstream file;

	file.open(path, std::ios::in);
	if (!file.good())
	{
		std::cerr << "File with sorce code couldn't open!" << std::endl;
		std::cerr << "File path:" << path << std::endl;
	}
	while (getline(file, line))
	{
		code += line + "\n";
	}
	file.close();

	return code;
}