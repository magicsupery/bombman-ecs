#ifndef _HPP_SKILL_HPP_
#define _HPP_SKILL_HPP_
#include "../ecs/component.h"
#include "../helper/utils.hpp"

namespace ecs
{

using SkillIdx2IdMap=
	BoomUnorderedMap<uint64_t, uint32_t>;

class ActiveSkill: public Component
{
public:
	virtual std::string name() {return "ActiveSkill";}
public:
	virtual Component::CompType getCompId() {return ActiveSkill::comp_id;}
	static Component::CompType comp_id;

public:
	//记录index对应的技能编号
	SkillIdx2IdMap idx2id_map_;
};

}// ecs
#endif
