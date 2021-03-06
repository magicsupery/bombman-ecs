#include "controller_system.h"
#include "move_system.h"
#include "skill_system.h"

#include "../ecs/entity_manager.h"
#include "../ecs/system_manager.h"

#include "../component/controller.hpp"

#include "../context/game_context.h"
#include "../helper/utils.hpp"
#include "../helper/const.hpp"

namespace ecs
{
System::SystemType ControllerSystem::system_id = SYSTEM_ID_CONTROLLER;

void ControllerSystem::tick(float dt)
{
	return;
	/*
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
	*/

}

void ControllerSystem::notify_keyboard_move_event_changed()
{
	auto p1 = GameContext::input_p1;
	if(p1 == nullptr)
		return;

	auto controller_comp_ptr = p1->getComponent<Controller>();
	if(controller_comp_ptr == nullptr)
		return;

	auto op = ControllerOpData::Nothing;
	if(GameContext::move_keyboardcode_vector.size() != 0)
	{
		auto last_keycode = GameContext::move_keyboardcode_vector.back();
		if(last_keycode == KeyboradCode::KEY_W)
		{
			op = ControllerOpData::Up;
		}
		else if(last_keycode == KeyboradCode::KEY_S)
		{
			op = ControllerOpData::Down;
		}
		else if(last_keycode == KeyboradCode::KEY_A)
		{
			op = ControllerOpData::Left;
		}
		else if(last_keycode == KeyboradCode::KEY_D)
		{
			op = ControllerOpData::Rigth;
		}
	}
	SystemManager::getInstance()->getSystem<MoveSystem>()->handleMoveOp(p1, op);

	/*
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
	*/
}

void ControllerSystem::notify_keyboard_skill_event_changed()
{

	auto p1 = GameContext::input_p1;
	if(p1 == nullptr)
		return;

	auto controller_comp_ptr = p1->getComponent<Controller>();
	if(controller_comp_ptr == nullptr)
		return;

	auto keyboard_bit = GameContext::keybord_bit;
	if((keyboard_bit & static_cast<uint64_t>(KeyboradCode::KEY_J)) != 0)
	{
		SystemManager::getInstance()->getSystem<SkillSystem>()->handleSkillOp(p1, ControllerOpData::SkillOne);
	}

}

} //ecs
