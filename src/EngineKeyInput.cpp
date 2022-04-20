#include "Engine.h"

void Geodash3::Engine::m_HandleKeyInput(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		xSpeed = 0.03f;	
	}
	else if(key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		xSpeed = -0.03f;	
	}
	else if(key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
	{
		xSpeed = 0.0f;	
	}
	else if(key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
	{
		xSpeed = 0.0f;	
	}
}
