#ifndef _HPP_SKILL_HPP_
#define _HPP_SKILL_HPP_

#include "../ecs/component.h"
namespace ecs
{
class Skill: public Component
{
public:
	virtual std::string name() {return "Skill";}
public:
	virtual Component::CompType getCompId() {return Skill::comp_id;}
	static Component::CompType comp_id;
};

}// ecs
#endif
