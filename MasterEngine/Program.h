#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

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
};