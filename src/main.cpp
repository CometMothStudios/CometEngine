#include <iostream>
#include <GLFW/glfw3.h>

int main()
{

	if (!glfwInit())
	{

		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;

	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "Comet Engine", NULL, NULL);

	if (!window)
	{

		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;

	}

	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();

		glfwSwapBuffers(window);

	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;

}