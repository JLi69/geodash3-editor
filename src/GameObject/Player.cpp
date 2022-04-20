#include "Player.h"

void Geodash3::Player::Update()
{
	//Move the player
	this->position += this->movement;
	
	//Player is above the ground, have gravity affect them
	if(this->position.y > -1.0f)
	{
		this->m_gravity = 0.01f;
		this->movement.y -= this->m_gravity;
		
		//Have the player spin
		this->rotation.x += 0.1f;
	}
	//Player is on ground, should not be affected by gravity
	else if(this->position.y <= -1.0f)
	{
		this->position.y = -1.0f;
		this->m_gravity = 0.0f;
		this->movement.y = 0.0f;

		this->rotation.x = 0.0f;
	}
}

Geodash3::Player::Player(glm::vec3 pos)
{
	//Set position of the player
	this->position = pos;
	//Player is 0.2 x 0.2 x 0.2 cube
	this->dimensions = glm::vec3(0.2f, 0.2f, 0.2f);
	//Player isn't rotated
	this->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	//Player starts out with no speed
	this->movement = glm::vec3(0.0f, 0.0f, 0.0f);

	//Force of gravity is 0
	this->m_gravity = 0.0f;
}
