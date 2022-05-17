#include "Engine.h"
#include <iostream>

void Geodash3::Engine::m_Update()
{
	//Update the camera
	this->m_camera.position += this->m_camera.movement * 1.0f / this->m_secondsToDrawFrame;
	//Rotate the camera
	this->m_camera.rotation.y += this->m_cameraRotationSpeed * 1.0f / this->m_secondsToDrawFrame;
	//Rotate camera based on mouse position
	double tempMouseX, tempMouseY;
	glfwGetCursorPos(this->m_gameWindow, &tempMouseX, &tempMouseY);
	if(glfwGetInputMode(this->m_gameWindow, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
		this->m_cameraRotationSpeed = 0.000015f * (float)(tempMouseX - this->m_mouseX);
	this->m_mouseX = tempMouseX;
	this->m_mouseY = tempMouseY;
}
