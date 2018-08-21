#include "render_system.h"

#include "../ecs/entity_manager.h"
#include "../component/transform.hpp"
#include "../component/model.hpp"

System::SystemType RenderSystem::system_id = 2;

void RenderSystem::tick(float dt)
{
	//tmp code show the entity pos
	auto model_ents_ptr = EntityManager::getInstance()->getEntitiesByComp<Model>();
	if(model_ents_ptr == nullptr)
		return;


	for(auto& model_ent_ptr : *model_ents_ptr)
	{

		auto model_comp_ptr = model_ent_ptr->getComponent<Model>();
		if(model_comp_ptr == nullptr)
			continue;

		auto transform_comp_ptr = model_ent_ptr->getComponent<Transform>();
		if(transform_comp_ptr == nullptr)
			continue;

		model_comp_ptr->model_sprite->setPosition(transform_comp_ptr->pos_x, transform_comp_ptr->pos_y);


	}
}
