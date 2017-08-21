#include "display.h"

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void processInput(GLFWwindow* window);

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
}

void Display::Update()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
	processInput(m_window);
}

int Display::IsClosed()
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

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

