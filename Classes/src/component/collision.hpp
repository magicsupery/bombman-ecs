#ifndef  _HPP_COLLISTION_HPP_
#define _HPP_COLLISTION_HPP_

#include "../ecs/component.h"
#include "../helper/utils.hpp"

namespace ecs
{
class Collision: public Component
{
public:
	Collision();
	~Collision();
	virtual std::string name() {return "Collision";}
public:
	virtual Component::CompType getCompId() {return Collision::comp_id;}
	static Component::CompType comp_id;

public:
	void createDebugDrawNode();
public:
	//现在只支持长方向的collistion
	BombRect collistion_rect;
	cocos2d::DrawNode* draw_node;
};

} //ecs
#endif
