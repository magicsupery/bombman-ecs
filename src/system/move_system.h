#ifndef _H_MOVESYSTEM_H_
#define _H_MOVESYSTEM_H_

#include "../ecs/system.h"

class MoveSystem : public System
{
public:
	virtual void tick(float dt);
};

#endif

