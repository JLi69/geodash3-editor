#include "Player.h"

void Geodash3::Player::Update(float secToDrawFrame)
{
	//Move the player
	this->position += this->movement * 1.0f / secToDrawFrame;
	//Move the collider
	this->m_collider.position = this->position;
	this->m_collider.position.y -= 0.05f;
	
	//Player is above the ground, have gravity affect them
	if(this->position.y > -1.8f)
		this->falling = true;
	else
		this->falling = false;

	if(this->falling)
	{
		this->m_gravity = 0.0002f;
		this->movement.y -= this->m_gravity;
		
		//Have the player spin
		this->rotation.x += 0.1f;
	}
	//Player is on ground, should not be affected by gravity
	else if(this->position.y <= -1.8f)
	{
		this->position.y = -1.8f;
		this->m_gravity = 0.0f;
		this->movement.y = 0.0f;

		this->rotation.x = 0.0f;

		this->canJump = true;
	}

	//Invisible borders for the player
	if(this->position.x < -0.8f || this->position.x > 0.8f)
	{
		this->position.x = (this->position.x < -0.8f) ? -0.8f : 0.8f;
		this->movement.x = 0.0f;
	}
}

Geodash3::Collider Geodash3::Player::getCollider()
{
	return this->m_collider;
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

	//Set up the collider
	this->m_collider.dimensions = this->dimensions;
	this->m_collider.position = this->position;

	//Force of gravity is 0
	this->m_gravity = 0.0f;
}
