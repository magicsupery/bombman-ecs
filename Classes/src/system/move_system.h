#ifndef _H_MOVESYSTEM_H_
#define _H_MOVESYSTEM_H_

#include "../ecs/system.h"
#include "../ecs/entity.hpp"

#include "../component/controller.hpp"

namespace ecs
{
class MoveSystem : public System
{
public:
	virtual void tick(float dt);
	virtual SystemType getSystemId() {return MoveSystem::system_id;}

	static SystemType system_id;

public:
	void handleMoveOp(EntityPtr ent_tpr, uint64_t op);
};
} //ecs
#endif

