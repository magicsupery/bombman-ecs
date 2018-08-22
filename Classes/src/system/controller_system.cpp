#include "controller_system.h"
#include "move_system.h"

#include "../ecs/entity_manager.h"
#include "../ecs/system_manager.h"

#include "../component/controller.hpp"

#include "../context/game_context.h"
#include "../helper/utils.hpp"

namespace ecs
{
System::SystemType ControllerSystem::system_id = 3;

void ControllerSystem::tick(float dt)
{

	auto controller_ents_ptr = EntityManager::getInstance()->getEntitiesByComp<Controller>();

	if(controller_ents_ptr == nullptr)
		return;

	for(auto& controller_ent_ptr: *controller_ents_ptr)
	{
		auto controller_comp_ptr = controller_ent_ptr->getComponent<Controller>();
		if(controller_comp_ptr == nullptr)
			continue;


		for(auto const& kv: controller_comp_ptr->op_map_)
		{
			if(kv.first == ControllerOp::Move)
			{
				SystemManager::getInstance()->getSystem<MoveSystem>()->handleMoveOp(controller_ent_ptr, kv.second);
			}

		}
		controller_comp_ptr->op_map_.clear();
	}

}

void ControllerSystem::notify_keyboard_move_event_changed()
{
	auto p1 = GameContext::input_p1;
	if(p1 == nullptr)
		return;

	auto controller_comp_ptr = p1->getComponent<Controller>();
	if(controller_comp_ptr == nullptr)
		return;

	controller_comp_ptr->clearOp(ControllerOp::Move);
	auto keyboard_bit = GameContext::keybord_bit;
	if((keyboard_bit & static_cast<uint64_t>(KeyboradCode::KEY_W)) != 0)
	{
		controller_comp_ptr->addOp(ControllerOp::Move, ControllerOpData::Up);
	}
	if((keyboard_bit & static_cast<uint64_t>(KeyboradCode::KEY_S)) != 0)
	{
		controller_comp_ptr->addOp(ControllerOp::Move, ControllerOpData::Down);
	}
	if((keyboard_bit & static_cast<uint64_t>(KeyboradCode::KEY_A)) != 0)
	{
		controller_comp_ptr->addOp(ControllerOp::Move, ControllerOpData::Left);
	}
	if((keyboard_bit & static_cast<uint64_t>(KeyboradCode::KEY_D)) != 0)
	{
		controller_comp_ptr->addOp(ControllerOp::Move, ControllerOpData::Rigth);
	}
}


} //ecs
