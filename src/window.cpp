#include "window.h"

#include <iostream>
#include <exception>

bool Window::m_init = true;

Window::Window() : m_window(nullptr)
{
	init();
}

Window::~Window()
{
	glfwTerminate();
}

void Window::init()
{
	if (m_init)
	{
		if (!glfwInit())
		{
			throw std::runtime_error("Error initializing GLFW\n");
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
}

void Window::initGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error("\nError loading OpenGL\n");
	}
}

auto Window::createWindow(const GLint& width, const GLint& height, const char* windowTitle) -> bool
{
	m_window = glfwCreateWindow(width, height, windowTitle, nullptr, nullptr);

	if (!m_window)
	{
		std::cerr << "\nCould not create window\n";
		return false;
	}

	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, &Window::framebufferSize);

	if (m_init)
	{
		initGlad();
		m_init = false;
	}

	return true;
}

auto Window::shouldClose() -> bool
{
	return glfwWindowShouldClose(m_window);
}

void Window::setFrameBufferSizeCallback(frameBufferSizeCallback fnc)
{
	glfwSetFramebufferSizeCallback(m_window, fnc);
}

void Window::framebufferSize(GLFWwindow* window, GLint width, GLint height)
{
	glViewport(0, 0, width, height);
}
