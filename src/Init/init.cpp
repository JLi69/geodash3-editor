#include <glad/glad.h>
#include "init.h"
#include <cstdlib>

void Geodash3::onWindowResize(GLFWwindow *win, int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
}

void Geodash3::init(GLFWwindow *&win, const char *title)
{
	if(!glfwInit())
		exit(-1);

	win = glfwCreateWindow(1920, 1080, title, NULL, NULL);
	if(!win)
	{
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(win);

	glfwSetWindowSizeCallback(win, Geodash3::onWindowResize);

	//Initialize glad
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		exit(-1);	
}
