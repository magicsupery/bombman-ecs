#ifndef _H_SKILLSYSTEM_H_
#define _H_SKILLSYSTEM_H_

#include "../ecs/system.h"
#include "../ecs/entity.hpp"

namespace ecs
{
class ActiveSkill;
class SkillSystem : public System
{
public:
	virtual void tick(float dt) {}
	virtual SystemType getSystemId() {return SkillSystem::system_id;}

	static SystemType system_id;

public:
	void handleSkillOp(EntityPtr ent_ptr, uint64_t op);
	void handleSkillId(EntityPtr ent_ptr, uint32_t skill_id);

private:
	void _handleSkill(std::shared_ptr<ActiveSkill> skill_comp_ptr, uint32_t skill_id);
};

} //ecs
#endif

