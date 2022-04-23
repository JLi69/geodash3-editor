#include "GameObject.h"

bool Geodash3::Collider::Colliding(Collider c1, Collider c2)
{
	return (c1.position.x > c2.position.x - c1.dimensions.x - c2.dimensions.x && c1.position.x < c2.position.x + c1.dimensions.x + c2.dimensions.x) &&
		   (c1.position.y > c2.position.y - c1.dimensions.y - c2.dimensions.y && c1.position.y < c2.position.y + c1.dimensions.y + c2.dimensions.y) &&
		   (c1.position.z > c2.position.z - c1.dimensions.z - c2.dimensions.z && c1.position.z < c2.position.z + c1.dimensions.z + c2.dimensions.z);
}
