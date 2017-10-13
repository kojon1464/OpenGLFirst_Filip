#pragma once

#include <glad\glad.h> 
#include <GLFW\glfw3.h>
#include <iostream>
#include "camera.h"

class Display
{
public:
	Display(int width, int height, const char* title);

	void update();
	int isClosed();
	void checkInput();
	Camera camera;

	virtual ~Display();
private:
	GLFWwindow* m_window;
};

