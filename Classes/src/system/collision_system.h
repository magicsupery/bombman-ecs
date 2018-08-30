#ifndef _H_COLLISIONSYSTEM_H_
#define _H_COLLISIONSYSTEM_H_

#include "../ecs/system.h"
#include "../ecs/entity.hpp"
#include "../helper/utils.hpp"

namespace ecs
{
class CollisionSystem : public System
{
public:
	virtual void tick(float dt);
	virtual SystemType getSystemId() {return CollisionSystem::system_id;}

	static SystemType system_id;

public:
	bool isCollision(const BombRect& rec1, const BombRect& rec2);
};
} //ecs
#endif

