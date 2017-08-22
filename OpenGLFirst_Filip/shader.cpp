#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexShaderCode, fragmentShaderCode, line;
	std::fstream vertexShaderFile, fragmentShaderFile;
	
	vertexShaderFile.open(vertexPath, std::ios::in);
	if (!vertexShaderFile.good())
	{
		std::cerr << "File with vertex shader code couldn't open!" << std::endl;
	}
	while (getline(vertexShaderFile, line))
	{
		vertexShaderCode += line + "\n";
	}
	vertexShaderFile.close();

	fragmentShaderFile.open(fragmentPath, std::ios::in);
	if (!fragmentShaderFile.good())
	{
		std::cerr << "File with fragment shader code couldn't open!" << std::endl;
	}
	while (getline(fragmentShaderFile, line))
	{
		fragmentShaderCode += line + "\n";
	}
	fragmentShaderFile.close();

	const char* vertexShaderSorce = vertexShaderCode.c_str();
	const char*	fragmentShaderSorce = fragmentShaderCode.c_str();

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

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &sucess);
	if (!sucess)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "Program failed to link shaders\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use() 
{
	glUseProgram(shaderProgram);
}

Shader::~Shader()
{
	glDeleteProgram(shaderProgram);
}
