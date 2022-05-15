#include "Spike.h"

void Geodash3::Spike::Update(float secToDrawFrame)
{
	//Move the spike
	this->position += this->movement * 1.0f / secToDrawFrame;

	//Move the colliders
	for(int i = 0; i < 4; i++)
		this->colliders[i].position += this->movement * 1.0f / secToDrawFrame;
}

Geodash3::Spike::Spike(glm::vec3 pos)
{
	//Set up the position
	this->position = pos;
	//Set up the dimensions, rotation, and movement of the spike
	this->dimensions = glm::vec3(0.25f, 0.25f, 0.25f);
	this->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	this->movement = glm::vec3(0.0f, 0.0f, 0.0015f);

	//Set up the colliders
	for(int i = 0; i < 4; i++)
	{
		this->colliders[i].dimensions.x = 0.15f - 0.03f * (float)i;
		this->colliders[i].dimensions.y = 0.25f / 6.0f;
		this->colliders[i].dimensions.z = 0.15f - 0.03f * (float)i;

		this->colliders[i].position.x = this->position.x;
		this->colliders[i].position.y = this->position.y + 0.25f / 6.0f * (float)i;
		this->colliders[i].position.z = this->position.z;
	}
}
