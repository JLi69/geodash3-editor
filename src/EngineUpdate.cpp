#include "Engine.h"

void Geodash3::Engine::m_Update()
{
	//TEST REMOVE LATER!!!
	static int timePassed = 0;

	//Update the player
	this->m_playerCube.Update();

	//Update the blocks
	for(auto &block : this->m_blocks)
		block.Update();

	//REMOVE LATER!!!	
	if(timePassed % 100 == 0)
		this->m_blocks.push_back(Geodash3::Block(glm::vec3((float)(rand() % 100) / 25.0f - 2.0f, -1.0f, -40.0f)));
	timePassed++;
}
