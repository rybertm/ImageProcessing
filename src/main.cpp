#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "timer.h"

#include <array>
#include <iostream>
#include <vector>
#include <cmath>

int WIDTH = 600;
int HEIGHT = 600;

auto main()	-> int
{
	if (!glfwInit())
	{
		std::cerr << "Error initializing GLFW\n";
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Janela", nullptr, nullptr);

	if (!window)
	{
		std::cerr << "Error creating window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Error loading OpenGL\n";
		return -1;
	}

	Shader shader;
	Timer timer;
	double tempo;

	timer.begin();
	shader.loadProgram("resources/shaders/ChaosGame.glsl");
	tempo = timer.elapsed();

	std::cout << "loadProgram finished in " << tempo << "ms\n";

	std::system("PAUSE");

	return 0;
}