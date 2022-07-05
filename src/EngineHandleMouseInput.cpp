#include "Engine.h"
#include <map>

void Geodash3::Engine::m_HandleMouseInput(GLFWwindow* win, int button, int action, int scancode)
{	
	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		//Interact with buttons on the pause menu
		if(this->m_paused && !this->m_help)
		{
			if(this->m_saveButton.MouseHovering(this->m_gameWindow, this->m_mouseX, this->m_mouseY))
				this->m_saveButton.Click();
			if(this->m_saveQuitButton.MouseHovering(this->m_gameWindow, this->m_mouseX, this->m_mouseY))
				this->m_saveQuitButton.Click();
			if(this->m_helpButton.MouseHovering(this->m_gameWindow, this->m_mouseX, this->m_mouseY))
				this->m_helpButton.Click();

			return;
		}
	}

	if(action == GLFW_PRESS)
		mouseHold[button] = true;
	else if(action == GLFW_RELEASE)
		mouseHold[button] = false;

	if(this->m_editMode == Geodash3::Mode::NORMAL)
		return;	
}
