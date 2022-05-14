#ifndef INCLUDE_GAMEOBJECT
#include "GameObject.h"
#endif

namespace Geodash3
{
	class Spike : public GameObject
	{
	public:
		Geodash3::Collider colliders[4];

		//Update the spike
		void Update(float secToDrawFrame);

		//Constructor
		Spike(glm::vec3 pos);
	};
};
