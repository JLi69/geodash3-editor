#include "Engine.h"

void Geodash3::Engine::m_HandleKeyInput(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	if(action == GLFW_PRESS)
	{
		switch(key)
		{
		case GLFW_KEY_A:
			this->m_playerCube.movement.x = -0.03f;
			break;
		case GLFW_KEY_D:
			this->m_playerCube.movement.x = 0.03f;
			break;
		//JUMP
		case GLFW_KEY_SPACE:
			this->m_playerCube.movement.y = 0.2f;
			break;
		}
	}
	else if(action == GLFW_RELEASE)
	{
		switch(key)
		{
		case GLFW_KEY_A:
			this->m_playerCube.movement.x = 0.0f;
			break;
		case GLFW_KEY_D:
			this->m_playerCube.movement.x = 0.0f;
			break;
		}
	}
}
