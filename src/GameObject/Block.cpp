#include "Block.h"

//Update function
void Geodash3::Block::Update(float secToDrawFrame)
{
	//Move the block
	this->position += this->movement * 1.0f / secToDrawFrame;
	//Move the collider
	this->m_collider.position = this->position;
}

Geodash3::Collider Geodash3::Block::getCollider()
{
	return this->m_collider;
}

//Constructor
Geodash3::Block::Block(glm::vec3 pos)
{
	//Set the position and dimensions of the block
	this->position = pos;
	this->dimensions = glm::vec3(0.25f, 0.25f, 0.25f);
	this->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	this->movement = glm::vec3(0.0f, 0.0f, 0.002f);

	//Set up the collider
	this->m_collider.dimensions = this->dimensions;
	this->m_collider.position = this->position;
}
