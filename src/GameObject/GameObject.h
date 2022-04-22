#define INCLUDE_GAMEOBJECT
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Geodash3
{
	//Box collider
	struct Collider
	{
		glm::vec3 position, //Position of the collider
				  dimensions; //How big the collider is

		//Returns true if colliding with another object
		//static bool Colliding(Collider c1, Collider c2);
	};

	//Game Object
	class GameObject
	{
	public:
		glm::vec3 position, //Position of object
				  movement, //Movement of object
				  rotation, //Rotation of object in degrees along x, y, and z axis
				  dimensions; //Dimensions of the object
	};
}
