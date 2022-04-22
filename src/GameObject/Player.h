#ifndef INCLUDE_GAMEOBJECT
#include "GameObject.h"
#endif

namespace Geodash3
{
	//Player object that inherits from the GameObject class
	class Player : public GameObject
	{
		float m_gravity; //Force of gravity on the player

		Collider m_collider; //Box collider for the player
	public:
		void Update(); //Update the player object

		//Constructor
		Player(glm::vec3 pos);
	};
}
