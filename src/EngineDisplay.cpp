#include "Engine.h"

void Geodash3::Engine::Display()
{
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

	GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 3));

	glfwSwapBuffers(gameWindow);
	glfwPollEvents();
}
