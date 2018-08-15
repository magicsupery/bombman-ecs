#include "controller_system.h"

#include "../ecs/entity_manager.h"
#include "../ecs/system_manager.h"

#include "../component/controller.hpp"

#include "move_system.h"

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
