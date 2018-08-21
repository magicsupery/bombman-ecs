#include "move_system.h"
#include "../ecs/entity_manager.h"
#include "../ecs/entity.hpp"
#include "../component/moveable.hpp"
#include "../component/transform.hpp"
#include "../component/controller.hpp"


System::SystemType MoveSystem::system_id = 1;

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
		auto dist_x = move_comp_ptr->speed_x * dt;
		auto dist_y = move_comp_ptr->speed_y * dt;
		transform_comp_ptr->pos_x += dist_x;
		transform_comp_ptr->pos_y += dist_y;
	}

}

void MoveSystem::handleMoveOp(EntityPtr ent_ptr, uint64_t op)
{
	// 可以根据ent_ptr的各种move属性来判断对应的op_data应该做什么操作，这里简单认为所有的ent都是一样的操作
	auto move_comp_ptr = ent_ptr->getComponent<Moveable>();
	if(move_comp_ptr == nullptr)
		return;

	move_comp_ptr->speed_x = (op & ControllerOpData::Rigth - op & ControllerOpData::Left) * move_comp_ptr->speed;
	move_comp_ptr->speed_y = (op & ControllerOpData::Down - op & ControllerOpData::Up) * move_comp_ptr->speed;
}
