#include "Engine.h"
#include <map>
#include <cmath>
#include <iostream>

void Geodash3::Engine::m_HandleKeyInput(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	static std::map<int, bool> s_keyPressed; //True if key is being held down, false if key isn't being held down
	const float speed = 6.0f; //Speed of the player
	
	if(action == GLFW_PRESS)
		s_keyPressed[key] = true;
	else if(action == GLFW_RELEASE)
		s_keyPressed[key] = false;
	
	//Move around
	//Move forward
	if(s_keyPressed[GLFW_KEY_W])
	{
		this->m_camera.movement.x = speed * sinf(-this->m_camera.rotation.y);
		this->m_camera.movement.z = speed * cosf(-this->m_camera.rotation.y);
	}
	//Move backwards
	else if(s_keyPressed[GLFW_KEY_S])
	{
		this->m_camera.movement.x = -speed * sinf(-this->m_camera.rotation.y);
		this->m_camera.movement.z = -speed * cosf(-this->m_camera.rotation.y);
	}
	//Move left	
	else if(s_keyPressed[GLFW_KEY_A])
	{	
		this->m_camera.movement.x = speed / 2.0f * sinf(-this->m_camera.rotation.y + 3.14159f / 2.0f);
		this->m_camera.movement.z = speed / 2.0f * cosf(-this->m_camera.rotation.y + 3.14159f / 2.0f);
	}
	//Move right
	else if(s_keyPressed[GLFW_KEY_D])
	{
		this->m_camera.movement.x = speed / 2.0f * sinf(-this->m_camera.rotation.y - 3.14159f / 2.0f);
		this->m_camera.movement.z = speed / 2.0f * cosf(-this->m_camera.rotation.y - 3.14159f / 2.0f);
	}
	//Stope moving
	else
	{
		this->m_camera.movement.x = 0.0f;
		this->m_camera.movement.z = 0.0f;
	}

	//Move camera up and down
	if(s_keyPressed[GLFW_KEY_SPACE])
		this->m_camera.movement.y = -4.0f;
	else if(s_keyPressed[GLFW_KEY_LEFT_SHIFT])
		this->m_camera.movement.y = 4.0f;
	else
		this->m_camera.movement.y = 0.0f;

	//Release/grab cursor
	if(s_keyPressed[GLFW_KEY_ESCAPE])
	{
		int mode = glfwGetInputMode(this->m_gameWindow, GLFW_CURSOR) == GLFW_CURSOR_DISABLED ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
		glfwSetInputMode(this->m_gameWindow, GLFW_CURSOR, mode);
		this->m_paused = !this->m_paused;
		this->m_help = false;	
		this->m_editMode = Geodash3::Mode::NORMAL;
	}

	//Change edit mode
	if(s_keyPressed[GLFW_KEY_1])
		this->m_editMode = Geodash3::Mode::NORMAL;
	if(s_keyPressed[GLFW_KEY_2])
		this->m_editMode = Geodash3::Mode::EDIT;

	//CTRL + E to save to a file
	if(s_keyPressed[GLFW_KEY_LEFT_CONTROL] && s_keyPressed[GLFW_KEY_E] || s_keyPressed[GLFW_KEY_RIGHT_CONTROL] && s_keyPressed[GLFW_KEY_E])
	{
		std::cout << "Attempted to save file\n";
		this->Write();
	}
}
