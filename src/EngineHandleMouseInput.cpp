#include "Engine.h"

void Geodash3::Engine::m_HandleMouseInput(GLFWwindow* win, int button, int action, int scancode)
{
	if(this->m_editMode == Geodash3::Mode::NORMAL)
		return;

	//Destroy a block
	if(button == GLFW_MOUSE_BUTTON_LEFT)
	{
		//Go through all the blocks and look for the block the user highlighted
		for(auto it = this->m_level.blocks.begin(); it != this->m_level.blocks.end(); it++)
		{
			if(it->position == -this->m_highlighted)
			{
				this->m_level.blocks.erase(it);
				break;
			}
		}
		//Go through all the spikes and look for the spike the user highlighted
		for(auto it = this->m_level.spikes.begin(); it != this->m_level.spikes.end(); it++)
		{
			if(it->position == -this->m_highlighted)
			{
				this->m_level.spikes.erase(it);
				break;
			}
		}
	}
	//Place a block
	else if(button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		//make sure that there is not an object in the current location
		bool canPlace = true;
		//Check through all the blocks	
		for(int i = 0; i < this->m_level.blocks.size() && canPlace; i++)
			if(this->m_level.blocks.at(i).position == -this->m_highlighted)
				canPlace = false;
		//Check through all the spikes
		for(int i = 0; i < this->m_level.spikes.size() && canPlace; i++)
			if(this->m_level.spikes.at(i).position == -this->m_highlighted)
				canPlace = false;

		if(this->m_currentBlockType != SPIKE)
		{
			if(canPlace)
			{
				Geodash3::Block tempBlock = Geodash3::Block(-this->m_highlighted);
				tempBlock.blockType = this->m_currentBlockType;
				this->m_level.blocks.push_back(tempBlock);
			}	
		}
		else if(this->m_currentBlockType == SPIKE)
		{	
			if(canPlace)
				this->m_level.spikes.push_back(Geodash3::Spike(-this->m_highlighted));	
		}
	}
}
