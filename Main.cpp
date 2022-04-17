#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
	//Initialize glfw
	if(!glfwInit())
		return -1;	

	//Initialize the window
	GLFWwindow* glWindow;
	glWindow = glfwCreateWindow(1920, 1080, "Geodash 3D", NULL, NULL);
	if(!glWindow)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(glWindow);

	//Initialize glad
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return -1;

	while(!glfwWindowShouldClose(glWindow))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(glWindow);
		glfwPollEvents();
	}

	glfwTerminate();
}
