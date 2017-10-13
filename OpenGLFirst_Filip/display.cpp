#include "display.h"

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Display::Display(int width, int height, const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (m_window == NULL)
	{
		std::cerr << "Failed to create window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
	}

	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

	camera = Camera();
}

void Display::checkInput()
{
	m_currentFrame = (float)glfwGetTime();
	float deltaTime = m_currentFrame - m_lastFrame;
	m_lastFrame = m_currentFrame;
	
	if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_window, true);
	}
	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.move(FORWARD, deltaTime);
	}
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.move(BACKWARD, deltaTime);
	}
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.move(LEFT, deltaTime);
	}
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.move(RIGHT, deltaTime);
	}
}

void Display::update()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

int Display::isClosed()
{
	return glfwWindowShouldClose(m_window);
}

Display::~Display()
{
	glfwTerminate();
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);	
}

