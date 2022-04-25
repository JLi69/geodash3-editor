#include "Engine.h"
#include <iostream>

void Geodash3::Engine::m_Update()
{
	//TEST REMOVE LATER!!!
	//static int timePassed = 0;

	//Update the player
	this->m_playerCube.Update();

	//Update the blocks
	bool hit = false; //Store if the player collided with a block
	for(auto &block : this->m_currentLevel.blocks)
	{
		//Check for collision
		if(Geodash3::Collider::Colliding(this->m_playerCube.getCollider(), block.getCollider()))
		{
			hit = true;
			this->m_playerCube.canJump = true;
			if(this->m_playerCube.falling)
				this->m_playerCube.position.y = block.position.y + this->m_playerCube.dimensions.y + block.dimensions.y;
			this->m_playerCube.falling = false;
			this->m_playerCube.movement.y = 0.0f;
			this->m_playerCube.rotation.x = 0.0f;
		}

		block.Update();
	}

	//Update the spikes
	for(auto &spike : this->m_currentLevel.spikes)
	{
		spike.Update();	
	}

	//Check if the player collided with a block
	if(!hit && this->m_playerCube.position.y > -1.8f)
		this->m_playerCube.falling = true;
	//If the player didn't collide with a block and isn't on the ground,
	//then that means that they cannot jump
	if(this->m_playerCube.falling)
		this->m_playerCube.canJump = false;

	//REMOVE LATER!!!	
	/*if(timePassed % 100 == 0)
	{
		for(float i = 0.0f; i < 4.0f; i++)
			for(float j = 0.0f; j < 3.0f; j++)
				this->m_blocks.push_back(Geodash3::Block(glm::vec3(-0.75f + 0.5f * i, -1.75f, -40.0f + 0.5f * j)));

		this->m_spikes.push_back(Geodash3::Spike(glm::vec3(-0.75f, -1.25f, -39.5f)));
		this->m_spikes.push_back(Geodash3::Spike(glm::vec3(-0.25f, -1.25f, -39.5f)));
		this->m_spikes.push_back(Geodash3::Spike(glm::vec3(0.25f, -1.25f, -39.5f)));	
		this->m_spikes.push_back(Geodash3::Spike(glm::vec3(0.75f, -1.25f, -39.5f)));	
	}

	timePassed++;*/
}
