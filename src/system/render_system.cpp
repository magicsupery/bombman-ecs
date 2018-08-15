#include "render_system.h"

#include "../ecs/entity_manager.h"
#include "../component/transform.hpp"

#include <iostream>

System::SystemType RenderSystem::system_id = 2;

void RenderSystem::tick(float dt)
{
	//tmp code show the entity pos
	auto transform_ents_ptr = EntityManager::getInstance()->getEntitiesByComp<Transform>();
	if(transform_ents_ptr == nullptr)
		return;


	for(auto& transform_ent_ptr : *transform_ents_ptr)
	{
		auto transform_comp_ptr = transform_ent_ptr->getComponent<Transform>();
		if(transform_comp_ptr == nullptr)
			continue;

		std::cout << "Entity "<< transform_ent_ptr << " posx is " << transform_comp_ptr->pos_x << " posy is " <<
			transform_comp_ptr ->pos_y << std::endl;
	}
}
