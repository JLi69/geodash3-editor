#ifndef INCLUDE_GAMEOBJECT
#include "GameObject.h"
#endif

namespace Geodash3
{
	class Block : public GameObject
	{
		Geodash3::Collider m_collider;
	public:
		int blockType = 0;

		//Update the block object
		void Update(float secToDrawFrame);

		//Return the collider
		Geodash3::Collider getCollider();

		//Constructor
		Block(glm::vec3 pos);
	};
}
