#include "Engine.h"
#include <iostream>

void Geodash3::Engine::m_Update()
{
	//Rotate camera based on mouse position
	double tempMouseX, tempMouseY;
	glfwGetCursorPos(this->m_gameWindow, &tempMouseX, &tempMouseY);
	if(glfwGetInputMode(this->m_gameWindow, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
	{
#ifndef WINDOWS
		this->m_cameraRotationSpeed = 0.1f * (float)floorf(tempMouseX - this->m_mouseX);
		this->m_cameraPitchSpeed = -0.1f * (float)floorf(tempMouseY - this->m_mouseY);
#else
		this->m_cameraRotationSpeed = 1.6f * (float)(tempMouseX - this->m_mouseX);
		this->m_cameraPitchSpeed = -1.6f * (float)(tempMouseY - this->m_mouseY);
#endif

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

	//Set the mouse position
	this->m_mouseX = tempMouseX;
	this->m_mouseY = tempMouseY;

	//Check if it is paused
	//If it is, don't update the scene
	if(this->m_paused)
	{
		this->m_cameraPitchSpeed = 0.0f;
		this->m_cameraRotationSpeed = 0.0f;
		return;
	}

	//Rotate the preview
	this->m_previewRotation += 1.35f * this->m_secondsToDrawFrame;

	//Update the camera
	this->m_camera.position += this->m_camera.movement * this->m_secondsToDrawFrame;
	//Rotate the camera
	this->m_camera.rotation.y += this->m_cameraRotationSpeed * this->m_secondsToDrawFrame;
	this->m_camera.rotation.x += this->m_cameraPitchSpeed * this->m_secondsToDrawFrame;

	//Camera boundaries
	if(this->m_camera.position.x < -1.0f)
		this->m_camera.position.x = -1.0f;
	else if(this->m_camera.position.x > 1.0f)
		this->m_camera.position.x = 1.0f;

	if(this->m_camera.position.y > 1.5f)
		this->m_camera.position.y = 1.5f;
	else if(this->m_camera.position.y < -5.0f)
		this->m_camera.position.y = -5.0f;

	//Current highlighted block	
	this->m_highlighted.x = glm::floor((this->m_camera.position.x + 2.0f * cosf(-this->m_camera.rotation.x) * sinf(-this->m_camera.rotation.y)) / 0.5f) * 0.5f + 0.25f;
	this->m_highlighted.y = glm::floor((this->m_camera.position.y + 2.0f * sinf(-this->m_camera.rotation.x)) / 0.5f) * 0.5f + 0.25f;
	this->m_highlighted.z = glm::floor((this->m_camera.position.z + 2.0f * cosf(-this->m_camera.rotation.x) * cosf(-this->m_camera.rotation.y)) / 0.5f) * 0.5f;

	if(-this->m_highlighted.x < -0.75f)
		this->m_highlighted.x = 0.75f;
	else if(-this->m_highlighted.x > 0.75f)
		this->m_highlighted.x = -0.75f;

	if(-this->m_highlighted.y > 3.75f)
		this->m_highlighted.y = -3.75f;
	else if(-this->m_highlighted.y < -1.75f)	
		this->m_highlighted.y = 1.75f;
}
