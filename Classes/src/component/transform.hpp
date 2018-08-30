#ifndef _HPP_TRANSFROM_HPP_
#define _HPP_TRANSFROM_HPP_

#include "../ecs/component.h"
#include "../helper/utils.hpp"
namespace ecs
{
class Transform: public Component
{
public:

	BombVec2 pos;
	virtual std::string name() { return "Transform";}

	virtual Component::CompType getCompId() {return Transform::comp_id;}
	static Component::CompType comp_id;
};

}
#endif

