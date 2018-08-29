#include "collision_system.h"

#include "../helper/const.hpp"
namespace ecs
{
System::SystemType CollisionSystem::system_id = SYSTEM_ID_COLLISION;

void CollisionSystem::tick(float dt)
{

}

bool CollisionSystem::isCollision(const EcsRect& rec1, const EcsRect& rec2)
{
	return true;
}

}//ecs
