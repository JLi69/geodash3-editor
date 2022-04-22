#ifndef INCLUDE_GAMEOBJECT
#include "GameObject.h"
#endif

namespace Geodash3
{
	class Block : public GameObject
	{
	public:
		//Update the block object
		void Update();

		//Constructor
		Block(glm::vec3 pos);
	};
}
