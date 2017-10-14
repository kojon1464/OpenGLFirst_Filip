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
	inline int getHeight() { return m_height; }
	inline int getWidth() { return m_width; }

	virtual ~Display();
private:
	GLFWwindow* m_window;
	friend static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	int m_width;
	int m_height;
};

