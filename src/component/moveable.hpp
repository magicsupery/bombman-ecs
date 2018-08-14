#ifndef _HPP_MOVEALBE_HPP_
#define  _HPP_MOVEALBE_HPP_

#include "../ecs/component.h"

class Moveable: public Component
{
public:
	int speed;
	int derection;
	virtual std::string name() {return "Moveable";}

	virtual Component::CompType getCompId() {return Moveable::comp_id;}
	static Component::CompType comp_id;
};

#endif

