#include "Program.h"

#pragma region ResizeEvent
void FrameBufferSizeCallBack(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
#pragma endregion

#pragma region InputEvents
void ProcessInput(GLFWwindow* window) 
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, true);
	}
}
#pragma endregion


Program::Program() 
{
	this->pResult = 0;
}

int Program::InitProgram() 
{
	this->pResult = InitGlfw();
	if (this->pResult != 0) 
	{
		return this->pResult;
	}

	this->pResult = InitWindow();
	if (this->pResult != 0) 
	{
		return this->pResult;
	}

	this->pResult = InitGlad();
	if (this->pResult != 0) 
	{
		return this->pResult;
	}

	this->pResult = Begin();

	glfwTerminate();
	return this->pResult;
}

int Program::InitWindow() 
{
	this->window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "MasterEngine 0.0.26", NULL, NULL);
	if (this->window == NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(this->window);
	return 0;
}

int Program::InitGlad() 
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	// 0, 0 set location of LOWER LEFT CORNER of the window size = size of glfwWindow
	glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
	glfwSetFramebufferSizeCallback(this->window, FrameBufferSizeCallBack);
}

int Program::InitGlfw() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	return 0;
}

int Program::Begin() 
{
	float triangle[] = { 
		-0.5f,-0.5f, 0.0f,
		0.5f,-0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	// Rendering Loop
	while (!glfwWindowShouldClose(this->window)) 
	{
		ProcessInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	return 0;
}

int main() 
{
	Program p = Program();
	return p.InitProgram();
}