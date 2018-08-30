#include "move_system.h"
#include "../ecs/entity_manager.h"
#include "../ecs/entity.hpp"
#include "../component/moveable.hpp"
#include "../component/transform.hpp"
#include "../component/controller.hpp"
#include "../component/collision.hpp"

#include "../helper/const.hpp"


namespace ecs
{
System::SystemType MoveSystem::system_id = SYSTEM_ID_MOVE;

void MoveSystem::tick(float dt)
{
	auto move_ents_ptr = EntityManager::getInstance()->getEntitiesByComp<Moveable>();
	if(move_ents_ptr == nullptr)
		return;

	for(auto& move_ent_ptr : *move_ents_ptr)
	{
		auto move_comp_ptr = move_ent_ptr->getComponent<Moveable>();
		if(move_comp_ptr == nullptr)
			continue;

		auto transform_comp_ptr = move_ent_ptr->getComponent<Transform>();
		if(transform_comp_ptr == nullptr)
			continue;

		//tmp code set the pos
		auto dist_x = move_comp_ptr->speed_vec.x * dt;
		auto dist_y = move_comp_ptr->speed_vec.y * dt;
		transform_comp_ptr->pos.x += dist_x;
		transform_comp_ptr->pos.y += dist_y;

		auto collision_comp_ptr = move_ent_ptr->getComponent<Collision>();
		if(collision_comp_ptr == nullptr)
			continue;

		auto& rect = collision_comp_ptr->collistion_rect;
		rect.origin.x += dist_x;
		rect.origin.y += dist_y;

		auto draw_node = collision_comp_ptr->draw_node;
		if(draw_node == nullptr)
			continue;

		draw_node->setPosition(cocos2d::Vec2(dist_x, dist_y) + draw_node->getPosition());
	}

}

void MoveSystem::handleMoveOp(EntityPtr ent_ptr, uint64_t op)
{
	// 可以根据ent_ptr的各种move属性来判断对应的op_data应该做什么操作，这里简单认为所有的ent都是一样的操作
	auto move_comp_ptr = ent_ptr->getComponent<Moveable>();
	if(move_comp_ptr == nullptr)
		return;

	int8_t x_bit = 0;
	if((op & ControllerOpData::Rigth) != 0)
		x_bit += 1;
	if((op & ControllerOpData::Left) != 0)
		x_bit -= 1;
	move_comp_ptr->speed_vec.x = x_bit * move_comp_ptr->speed;

	int8_t y_bit = 0;
	if((op & ControllerOpData::Up) != 0)
		y_bit += 1;
	if((op & ControllerOpData::Down) != 0)
		y_bit -= 1;
	move_comp_ptr->speed_vec.y = y_bit * move_comp_ptr->speed;

}

} //ecs
