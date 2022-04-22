#include "Block.h"

//Update function
void Geodash3::Block::Update()
{
	this->position += this->movement;
}

//Constructor
Geodash3::Block::Block(glm::vec3 pos)
{
	//Set the position and dimensions of the block
	this->position = pos;
	this->dimensions = glm::vec3(0.25f, 0.25f, 0.25f);
	this->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	this->movement = glm::vec3(0.0f, 0.0f, 0.07f);
}
