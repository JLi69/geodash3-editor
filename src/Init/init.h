#include <GLFW/glfw3.h>

namespace Geodash3
{
	//Handle window resizing
	void onWindowResize(GLFWwindow *win, int newWidth, int newHeight); 

	//Initialize variables
	void init(GLFWwindow *&win, const char *title);
}
