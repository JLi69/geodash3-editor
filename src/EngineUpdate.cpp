#include "Engine.h"

void Geodash3::Engine::m_Update()
{
	x += xSpeed;

	if(x < -2.0f || x > 2.0f)
	{
		x -= xSpeed;
		xSpeed = 0.0f;
	}
}
