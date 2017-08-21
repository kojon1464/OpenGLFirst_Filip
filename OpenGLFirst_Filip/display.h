#include <glad\glad.h> 
#include <GLFW\glfw3.h>
#include <iostream>

class Display
{
public:
	Display(int width, int height, const char* title);

	void Update();
	int IsClosed();

	virtual ~Display();
private:
	GLFWwindow* m_window;
};

