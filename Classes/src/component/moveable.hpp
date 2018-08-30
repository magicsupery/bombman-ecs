#ifndef _HPP_MOVEALBE_HPP_
#define  _HPP_MOVEALBE_HPP_

#include "../ecs/component.h"
#include "../helper/utils.hpp"

namespace ecs
{
class Moveable: public Component
{
public:
	BombVec2 speed_vec;
	double speed;
	virtual std::string name() {return "Moveable";}
public:
	virtual Component::CompType getCompId() {return Moveable::comp_id;}
	static Component::CompType comp_id;
};

}
#endif

