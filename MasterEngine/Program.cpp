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


AEngine::Program::Program()
{
	this->pResult = 0;
}

int AEngine::Program::InitProgram() 
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

int AEngine::Program::InitWindow() 
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

int AEngine::Program::InitGlad() 
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

int AEngine::Program::InitGlfw() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	return 0;
}

int AEngine::Program::Begin() 
{
	// Define the triangle's vertices
	float triangle[] = { 
		-0.5f,-0.5f, 0.0f,
		0.5f,-0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	// Create the vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR: Vertex Shader Compilation Failed" << "\n" << infoLog << std::endl;
		return -1;
	}

	// Create the fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR: Fragment Shader Compilation Failed" << "\n" << infoLog << std::endl;
		return -1;
	}

	// Create the shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) 
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR: Shader Program Compilation Failed" << "\n" << infoLog << std::endl;
		return -1;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int VertexBufferObject, VertexArrayObject;
	glGenVertexArrays(1, &VertexArrayObject);
	glGenBuffers(1, &VertexBufferObject);

	glBindVertexArray(VertexArrayObject);
	
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Rendering Loop
	while (!glfwWindowShouldClose(this->window)) 
	{
		ProcessInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VertexArrayObject);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	return 0;
}

int main() 
{
	AEngine::Program p = AEngine::Program();
	return p.InitProgram();
}