#include "entity_factory.h"
#include "../ecs/entity_manager.h"
#include "../component/transform.hpp"
#include "../component/moveable.hpp"
#include "../component/controller.hpp"
#include "../component/model.hpp"
#include "../component/skill.hpp"

#include "../context/game_context.h"
#include "../helper/utils.hpp"

namespace ecs
{
EntityFactory* EntityFactory::instance_ = nullptr;

EntityFactory::EntityFactory()
{

}

EntityFactory::~EntityFactory()
{

}

EntityFactory* EntityFactory::getInstance()
{
	if(instance_ == nullptr)
		instance_ = new EntityFactory();
	return instance_;
}

EntityPtr EntityFactory::createP1()
{

	auto entity_ptr = std::make_shared<Entity>();

	auto comp_ptr = std::make_shared<Transform>();
	entity_ptr->addComponent(comp_ptr);

	auto comp_ptr_2 = std::make_shared<Moveable>();
	comp_ptr_2->speed_x = 0;
	comp_ptr_2->speed_y = 0;
	comp_ptr_2->speed = 0.05;
	entity_ptr->addComponent(comp_ptr_2);

	auto comp_ptr_3 = std::make_shared<Controller>();
	entity_ptr->addComponent(comp_ptr_3);

	auto model_ptr = std::make_shared<Model>();
	model_ptr->create_model("p1.png");
	entity_ptr->addComponent(model_ptr);

	auto skill_ptr = std::make_shared<ActiveSkill>();
	//todo parse from data
	skill_ptr->idx2id_map_[ControllerOpData::SkillOne] = 1;
	entity_ptr->addComponent(skill_ptr);

	EntityManager::getInstance()->addEntity(entity_ptr);

	GameContext::input_p1 = entity_ptr;

	return entity_ptr;
}

} //ecs
