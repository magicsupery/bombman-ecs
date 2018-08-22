#include "skill_system.h"
#include "../helper/const.hpp"
#include "../component/skill.hpp"
#include "../log/logging.h"

namespace ecs
{
System::SystemType SkillSystem::system_id = SYSTEM_ID_SKILL;


void SkillSystem::handleSkillOp(EntityPtr ent_ptr, uint64_t op_data)
{
	auto skill_comp_ptr = ent_ptr->getComponent<ActiveSkill>();
	if(skill_comp_ptr == nullptr)
		return;

	if(skill_comp_ptr->idx2id_map_.find(op_data) == skill_comp_ptr->idx2id_map_.end())
		return;

	auto skill_id = skill_comp_ptr->idx2id_map_[op_data];
	_handleSkill(skill_comp_ptr, skill_id);

}

void SkillSystem::handleSkillId(EntityPtr ent_ptr, uint32_t skill_id)
{
	auto skill_comp_ptr = ent_ptr->getComponent<ActiveSkill>();
	if(skill_comp_ptr == nullptr)
		return;

	_handleSkill(skill_comp_ptr, skill_id);
}

void SkillSystem::_handleSkill(std::shared_ptr<ActiveSkill> skill_comp_ptr, uint32_t skill_id)
{
	BOMBLOG("use skill %ld", skill_id);
}

} //ecs
