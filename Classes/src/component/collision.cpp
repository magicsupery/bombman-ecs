#include "collision.hpp"
#include "../helper/const.hpp"
#include "../context/game_context.h"

namespace ecs
{
Component::CompType Collision::comp_id = COMPONENT_ID_COLLISION;

Collision::Collision():
	draw_node(nullptr)
{

}
Collision::~Collision()
{
	if(draw_node != nullptr)
	{
		draw_node->removeFromParent();
		draw_node = nullptr;
	}

}

void Collision::createDebugDrawNode()
{
	draw_node = cocos2d::DrawNode::create();
	cocos2d::Vec2 rectangle[4];
	auto& rect = collistion_rect;
	rectangle[0] = cocos2d::Vec2(rect.origin.x, rect.origin.y);
	rectangle[1] = cocos2d::Vec2(rect.origin.x, rect.origin.y + rect.size.height);
	rectangle[2] = cocos2d::Vec2(rect.origin.x + rect.size.width, rect.origin.y+ rect.size.height);
	rectangle[3] = cocos2d::Vec2(rect.origin.x + rect.size.width, rect.origin.y);

	cocos2d::Color4F red(1, 0, 0, 1);
	draw_node->drawPolygon(rectangle, 4, red, 1, red);
	GameContext::running_scene->addChild(draw_node, 2);
}

}
