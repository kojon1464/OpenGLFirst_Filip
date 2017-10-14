#include "display.h"

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

float lastX = 400, lastY = 300;
float currentFrame = 0;
float lastFrame = 0;
float pitch = 0, yaw = -90;
bool firstmouse = true;

Display::Display(int width, int height, const char* title)
{
	m_width = width;
	m_height = height;

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
	glfwSetCursorPosCallback(m_window, mouse_callback);

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetWindowUserPointer(m_window, this);
}

void Display::checkInput()
{
	currentFrame = (float)glfwGetTime();
	float deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	
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
	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	front = glm::normalize(front);
	camera.setFront(front);
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
	Display* dis = (Display*)glfwGetWindowUserPointer(window);
	dis->m_height = height;
	dis->m_width = width;
}

static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if(firstmouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstmouse = false;
	}
	
	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos;
	lastX = (float)xpos;
	lastY = (float)ypos;

	float sensivity = 0.2f;
	xoffset *= sensivity;
	yoffset *= sensivity;

	yaw += xoffset;
	pitch += yoffset;
	
	if (pitch >= 89.0f) pitch = 89.0f;
	if (pitch <= -89.0) pitch = -89.0f;
}


