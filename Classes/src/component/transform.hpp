#ifndef _HPP_TRANSFROM_HPP_
#define _HPP_TRANSFROM_HPP_

#include "../ecs/component.h"
namespace ecs
{
class Transform: public Component
{
public:
	double pos_x;
	double pos_y;

	virtual std::string name() { return "Transform";}

	virtual Component::CompType getCompId() {return Transform::comp_id;}
	static Component::CompType comp_id;
};

}
#endif

