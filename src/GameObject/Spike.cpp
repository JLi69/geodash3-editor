#include "Spike.h"

void Geodash3::Spike::Update()
{
	//Move the spike
	this->position += this->movement;
}

Geodash3::Spike::Spike(glm::vec3 pos)
{
	//Set up the position
	this->position = pos;
	//Set up the dimensions, rotation, and movement of the spike
	this->dimensions = glm::vec3(0.25f, 0.25f, 0.25f);
	this->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	this->movement = glm::vec3(0.0f, 0.0f, 0.1f);

	//Set up the colliders
}
