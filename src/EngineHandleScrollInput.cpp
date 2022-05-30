#include "Engine.h"

void Geodash3::Engine::m_HandleScrollInput(GLFWwindow* win, double xoffset, double yoffset)
{
	//Detect vertical scrolling
	if(yoffset > 0.9)
	{
		this->m_currentBlockType++;
	}
	else if(yoffset < -0.9)
	{
		this->m_currentBlockType--;	
	}

	if(this->m_currentBlockType < BLOCK1)
		this->m_currentBlockType = BLOCK1;
	else if(this->m_currentBlockType > SPIKE)
		this->m_currentBlockType = SPIKE;
}
