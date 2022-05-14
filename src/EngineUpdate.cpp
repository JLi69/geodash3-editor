#include "Engine.h"
#include <iostream>

void Geodash3::Engine::m_Update()
{
	//TEST REMOVE LATER!!!
	//static int timePassed = 0;

	//Update the player
	this->m_playerCube.Update(this->m_secondsToDrawFrame);

	//Update the blocks
	bool hit = false; //Store if the player collided with a block
	for(auto &block : this->m_currentLevel.blocks)
	{
		//Check for collision
		if(Geodash3::Collider::Colliding(this->m_playerCube.getCollider(), block.getCollider()))
		{
			hit = true;
			this->m_playerCube.canJump = true;	
			//Player hits the cube head on
			if(this->m_playerCube.position.z <= block.position.z - block.dimensions.z - this->m_playerCube.position.z &&
				this->m_playerCube.position.y > block.position.y - block.dimensions.y &&
				this->m_playerCube.position.y < block.position.y + block.dimensions.y)
			{
				//Reset the player and level
				this->m_playerCube = Geodash3::Player(glm::vec3(0.0f, -1.8f, -4.5f));
				this->m_currentLevel = Geodash3::LoadLevel("res/levels/level0.lvl");	
				return;
			}
			//Player is moving left and right and hits the cube
			/*if(this->m_playerCube.position.x >= block.position.x + block.dimensions.x + this->m_playerCube.dimensions.x && 
				this->m_playerCube.position.y > block.position.y - block.dimensions.y &&
				this->m_playerCube.position.y < block.position.y + block.dimensions.y ||

				this->m_playerCube.position.x <= block.position.x - block.dimensions.x - this->m_playerCube.dimensions.x &&
				this->m_playerCube.position.y > block.position.y - block.dimensions.y &&
				this->m_playerCube.position.y < block.position.y + block.dimensions.y)
			{
				this->m_playerCube.movement.x *= -1;
				this->m_playerCube.Update();
				this->m_playerCube.movement.x *= -1;
				block.Update();
				continue;
			}*/
			//Player fell on top of the cube
			if(this->m_playerCube.falling)
				this->m_playerCube.position.y = block.position.y + this->m_playerCube.dimensions.y + block.dimensions.y;	

			this->m_playerCube.falling = false;
			this->m_playerCube.movement.y = 0.0f;
			this->m_playerCube.rotation.x = 0.0f;
		}

		block.Update(this->m_secondsToDrawFrame);
	}

	//Update the spikes
	for(auto &spike : this->m_currentLevel.spikes)
	{
		//Check for collisions
		for(int i = 0; i < 4; i++)
		{
			//Check for collision
			if(Geodash3::Collider::Colliding(this->m_playerCube.getCollider(), spike.colliders[i]))
			{
				//Reset the player and level
				this->m_playerCube = Geodash3::Player(glm::vec3(0.0f, -1.8f, -4.5f));
				this->m_currentLevel = Geodash3::LoadLevel("res/levels/level0.lvl");	
				return;
			}
		}

		spike.Update(this->m_secondsToDrawFrame);	
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
