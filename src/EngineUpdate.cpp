#include "Engine.h"
#include <iostream>

void Geodash3::Engine::m_Update()
{
	//Update the camera
	this->m_camera.position += this->m_camera.movement * 1.0f / this->m_secondsToDrawFrame;
	//Rotate the camera
	this->m_camera.rotation.y += this->m_cameraRotationSpeed * 1.0f / this->m_secondsToDrawFrame;
	this->m_camera.rotation.x += this->m_cameraPitchSpeed * 1.0f / this->m_secondsToDrawFrame;
	//Rotate camera based on mouse position
	double tempMouseX, tempMouseY;
	glfwGetCursorPos(this->m_gameWindow, &tempMouseX, &tempMouseY);
	if(glfwGetInputMode(this->m_gameWindow, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
	{
		this->m_cameraRotationSpeed = 0.000015f * (float)(tempMouseX - this->m_mouseX);
		this->m_cameraPitchSpeed = -0.000005f * (float)(tempMouseY - this->m_mouseY);
	

		if(this->m_camera.rotation.x < -3.14159f / 2.0f)
			this->m_camera.rotation.x = -3.14159f / 2.0f;
		if(this->m_camera.rotation.x > 3.14159f / 2.0f)
			this->m_camera.rotation.x = 3.14159f / 2.0f;
	}
	else
	{
		this->m_cameraRotationSpeed = 0.0f;
		this->m_cameraPitchSpeed = 0.0f;
	}
	this->m_mouseX = tempMouseX;
	this->m_mouseY = tempMouseY;

	//Current highlighted block	
	highlighted.x = glm::floor((this->m_camera.position.x + 2.0f * cosf(-this->m_camera.rotation.x) * sinf(-this->m_camera.rotation.y)) / 0.5f) * 0.5f + 0.25f;
	highlighted.y = glm::floor((this->m_camera.position.y - 0.2f + 2.0f * sinf(-this->m_camera.rotation.x)) / 0.5f) * 0.5f + 0.25f;
	highlighted.z = glm::floor((this->m_camera.position.z + 2.0f * cosf(-this->m_camera.rotation.x) * cosf(-this->m_camera.rotation.y)) / 0.5f) * 0.5f;
}
