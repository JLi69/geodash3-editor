#include <glad/glad.h>
#include "init.h"
#include <cstdlib>

void Geodash3::init(GLFWwindow *&win, const char *title, GLFWwindowsizefun onWindowResize)
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

	glfwSetWindowSizeCallback(win, onWindowResize);

	//Initialize glad
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		exit(-1);
}
