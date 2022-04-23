#include "Engine.h"
#include <iostream>

void Geodash3::Engine::m_Update()
{
	//TEST REMOVE LATER!!!
	static int timePassed = 0;

	//Update the player
	this->m_playerCube.Update();

	//Update the blocks
	bool hit = false;
	for(auto &block : this->m_blocks)
	{
		if(Geodash3::Collider::Colliding(this->m_playerCube.getCollider(), block.getCollider()))
		{
			hit = true;	
			this->m_playerCube.position.y = block.position.y + this->m_playerCube.dimensions.y + block.dimensions.y;
			this->m_playerCube.movement.y = 0.0f;
			this->m_playerCube.rotation.x = 0.0f;
		}

		block.Update();
	}

	if(!hit)
		this->m_playerCube.falling = true;

	//REMOVE LATER!!!	
	if(timePassed % 100 == 0)
	{
		for(float i = 0.0f; i < 4.0f; i++)
			for(float j = 0.0f; j < 3.0f; j++)
				this->m_blocks.push_back(Geodash3::Block(glm::vec3(-0.75f + 0.5f * i, -1.75f, -40.0f + 0.5f * j)));
	}
	timePassed++;

	//std::cout << "Player pos: " << this->m_playerCube.position.x << ", " << this->m_playerCube.position.y << ", " << this->m_playerCube.position.y << '\n';
}
