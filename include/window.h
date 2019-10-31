#include <glad/glad.h>
#include <GLFW/glfw3.h>

using frameBufferSizeCallback = void (*)(GLFWwindow*, int, int);

class Window
{
public:
	Window();
	~Window();

	auto createWindow(const GLint& width, const GLint& height, const char* windowTitle) -> bool;
	auto shouldClose() -> bool;

	void setFrameBufferSizeCallback(frameBufferSizeCallback fnc);


private:
	GLFWwindow* m_window;
	static bool m_init;

	static void init();
	static void initGlad();
	static void framebufferSize(GLFWwindow* window, GLint width, GLint height);
};
