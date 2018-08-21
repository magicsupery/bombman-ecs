#ifndef _HPP_MOVEALBE_HPP_
#define  _HPP_MOVEALBE_HPP_

#include "../ecs/component.h"

class Moveable: public Component
{
public:
	double speed_x;
	double speed_y;
	double speed;
	virtual std::string name() {return "Moveable";}
public:
	virtual Component::CompType getCompId() {return Moveable::comp_id;}
	static Component::CompType comp_id;
};

#endif

