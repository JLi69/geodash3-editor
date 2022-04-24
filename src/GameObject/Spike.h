#ifndef INCLUDE_GAMEOBJECT
#include "GameObject.h"
#endif

namespace Geodash3
{
	class Spike : public GameObject
	{
	public:
		//Update the spike
		void Update();

		//Constructor
		Spike(glm::vec3 pos);
	};
};
