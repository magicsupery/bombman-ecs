#ifndef _H_SKILLSYSTEM_H_
#define _H_SKILLSYSTEM_H_

#include "../ecs/system.h"
#include "../ecs/entity.hpp"

namespace ecs
{
class SkillSystem : public System
{
public:
	virtual void tick(float dt) {}
	virtual SystemType getSystemId() {return SkillSystem::system_id;}

	static SystemType system_id;

public:
	void handleSkillOp(EntityPtr ent_tpr, uint64_t op);
};

} //ecs
#endif

