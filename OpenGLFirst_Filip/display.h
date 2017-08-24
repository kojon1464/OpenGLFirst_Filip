#pragma once

#include <glad\glad.h> 
#include <GLFW\glfw3.h>
#include <iostream>

class Display
{
public:
	Display(int width, int height, const char* title);

	void update();
	int isClosed();

	virtual ~Display();
private:
	GLFWwindow* m_window;
};

