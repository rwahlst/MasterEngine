#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define POLY_MODE false

namespace AEngine
{

	class Program
	{
	public:
		Program();
		int InitProgram();
	private:
		int InitGlfw();
		int InitWindow();
		int InitGlad();
		int Begin();
		GLFWwindow* window;
		int pResult = 0;
		const char* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";
		const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"}\0";
	};
}