#include "Engine.h"

void Geodash3::Engine::m_OnWindowResize(GLFWwindow *win, int newWidth, int newHeight)
{
	GL_CALL(glViewport(0, 0, newWidth, newHeight));
	float aspect = (float)newWidth / (float)newHeight;
	this->m_perspectiveMat = glm::perspective(FOV * 3.14159f / 180.0f, aspect, 0.1f, 1000.0f);
}
