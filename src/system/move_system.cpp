#include "move_system.h"
#include "../ecs/entity_manager.h"
#include "../ecs/entity.hpp"
#include "../component/moveable.hpp"
#include "../component/transform.hpp"

void MoveSystem::tick(float dt)
{
	auto move_ents_ptr = EntityManager::getInstance()->getEntitiesByComp(2);
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
		auto dist = move_comp_ptr->speed * dt;
		if(move_comp_ptr->derection == 1)
			transform_comp_ptr->pos_x += dist;
		else if(move_comp_ptr->derection == 2)
			transform_comp_ptr->pos_x -= dist;
		else if(move_comp_ptr->derection == 3)
			transform_comp_ptr->pos_y += dist;
		else if(move_comp_ptr->derection == 4)
			transform_comp_ptr->pos_y -= dist;

	}

}
