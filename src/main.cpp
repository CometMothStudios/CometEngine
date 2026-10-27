#include "../external/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "Time.hpp"
#include "Shader.hpp"


int main()
{

	if (!glfwInit())
	{

		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;

	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(640, 480, "Comet Engine", NULL, NULL);

	if (!window)
	{

		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;

	}

	glfwMakeContextCurrent(window);

	// -- Initialize GLAD --
	// Pass GLAD the adress of GLFW's function to load the OpenGL function pointers

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD (OpenGL Loader)" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	Shader myShader("shaders/default.vert", "shaders/default.frag");

			// -- Make Triangle --

	// 1. Define the 4 unique corners of a square (X, Y, Z)
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // 0: Top Right
		 0.5f, -0.5f, 0.0f,  // 1: Bottom Right
		-0.5f, -0.5f, 0.0f,  // 2: Bottom Left
		-0.5f,  0.5f, 0.0f   // 3: Top Left 
	};

	// 2. Map out how to connect the dots (Indices)
	unsigned int indices[] = {
		0, 1, 3,  // First Triangle (Top Right, Bottom Right, Top Left)
		1, 2, 3   // Second Triangle (Bottom Right, Bottom Left, Top Left)
	};


	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	Time engineTime(60.0f);

	float fpsTimer = 0.0f;
	int frameCount = 0;

	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();

		engineTime.Tick();

		while (engineTime.ConsumeFixedSteps())
		{

			// Update game logic here

		}

				// --- RENDER PHASE ---
		glClearColor(0.1f, 0.15f, 0.22f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.Use();
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		glfwSwapBuffers(window);


		frameCount++;
		fpsTimer += engineTime.GetDeltaTime();
		if (fpsTimer >= 1.0f)
		{
			std::cout << "Engine FPS: " << frameCount << std::endl;
			frameCount = 0;
			fpsTimer = 0.0f;
		}

	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;

};