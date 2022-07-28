#include "Button.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

void Geodash3::Button::Click()
{
	this->m_onClick();	
}

void Geodash3::Button::SetButtonTex(std::string texPath)
{
	this->m_buttonTex = TextureObj(texPath);
}

void Geodash3::Button::ActivateButtonTex()
{
	this->m_buttonTex.ActivateTexture(GL_TEXTURE0);
}

bool Geodash3::Button::MouseHovering(GLFWwindow *win, double mouseX, double mouseY)
{
	int winWidth, winHeight;
	glfwGetWindowSize(win, &winWidth, &winHeight);

	return (float)mouseX / (float)winWidth * 2.0f - 1.0f > this->m_position.x / 0.11f - this->m_dimensions.x / 0.11f &&
		   (float)mouseX / (float)winWidth * 2.0f - 1.0f < this->m_position.x / 0.11f + this->m_dimensions.x / 0.11f &&
		   ((float)mouseY / (float)winHeight * 2.0f - 1.0f) * -1.0f > this->m_position.y / 0.11f * (float)winWidth / (float)winHeight - this->m_dimensions.y / 0.11f * (float)winWidth / (float)winHeight &&
		   ((float)mouseY / (float)winHeight * 2.0f - 1.0f) * -1.0f < this->m_position.y / 0.11f * (float)winWidth / (float)winHeight + this->m_dimensions.y / 0.11f * (float)winWidth / (float)winHeight;
}

void Geodash3::Button::SetModelViewMat(glm::mat4 &modelViewMat)
{
	modelViewMat = glm::translate(glm::mat4(1.0f), glm::vec3(this->m_position.x, this->m_position.y, -0.11f)) *  
				   glm::scale(glm::mat4(1.0f), glm::vec3(this->m_dimensions.x, this->m_dimensions.y, 1.0f));	
}

Geodash3::Button::Button(std::function<void()> clickFunc, glm::vec2 position, glm::vec2 dimensions)
{
	this->m_onClick = clickFunc;
	this->m_position = position;
	this->m_dimensions = dimensions;
}

Geodash3::Button::Button()
{
	this->m_position = glm::vec2(0.0f, 0.0f);
	this->m_dimensions = glm::vec2(0.0f, 0.0f);
}
