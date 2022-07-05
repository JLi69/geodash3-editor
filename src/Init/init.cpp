#include <glad/glad.h>
#include "init.h"
#include <cstdlib>

void Geodash3::init(GLFWwindow *&win, const char *title)
{
	if(!glfwInit())
		exit(-1);

	win = glfwCreateWindow(1200, 675, title, NULL, NULL);
	if(!win)
	{
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(win);

	//Initialize glad
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		exit(-1);
}
