#include "entity_manager.h"
#include "entity.hpp"

#include <iostream>
namespace ecs
{
EntityManager* EntityManager::instance_ = nullptr;

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{
	entities_.clear();
	comp_entities_.clear();
}

EntityManager* EntityManager::getInstance()
{
	if(instance_ == nullptr)
		instance_ = new EntityManager();
	return instance_;
}

void EntityManager::addEntity(EntityPtr ent_ptr)
{
	// add comp related idx
	auto comp_ids = ent_ptr->getComponentIds();
	for(auto comp_id : comp_ids)
	{
		notifyAddComponent(ent_ptr, comp_id);
	}

	// add ents
	entities_.emplace_back(ent_ptr);
	ent_ptr->set_idx(entities_.size() - 1);

}

void EntityManager::removeEntity(EntityPtr ent_ptr)
{
	// remove comp related idx
	auto comp_ids = ent_ptr->getComponentIds();
	for(auto comp_id : comp_ids)
	{
		notifyRemoveComponent(ent_ptr, comp_id);
	}

	// remove ents
	auto swap_ent_ptr = entities_[entities_.size() - 1];
	if(ent_ptr == swap_ent_ptr)
	{
		entities_.pop_back();
	}
	else
	{
		auto idx = ent_ptr->get_idx();
		swap_ent_ptr->set_idx(idx);
		entities_[idx] = swap_ent_ptr;
		entities_.pop_back();
	}

	ent_ptr->clear_idx();

}

void EntityManager::notifyAddComponent(EntityPtr ent_ptr, Component::CompType comp_id)
{
	if(comp_entities_.find(comp_id) == comp_entities_.end())
		comp_entities_[comp_id] = std::vector<EntityPtr>();

	auto& ent_ptr_vector = comp_entities_[comp_id];
	ent_ptr_vector.emplace_back(ent_ptr);
	ent_ptr->set_comp_idx(comp_id, ent_ptr_vector.size() - 1);
}

void EntityManager::notifyRemoveComponent(EntityPtr ent_ptr, Component::CompType comp_id)
{

	if(comp_entities_.find(comp_id) == comp_entities_.end())
		return;


	auto& ent_ptr_vector = comp_entities_[comp_id];
	auto swap_ent_ptr = ent_ptr_vector[ent_ptr_vector.size() - 1];

	if(ent_ptr == swap_ent_ptr)
	{
		ent_ptr_vector.pop_back();
	}
	else
	{
		auto idx = ent_ptr->get_comp_idx(comp_id);
		ent_ptr->set_comp_idx(comp_id, idx);
		ent_ptr_vector[idx] = swap_ent_ptr;
		ent_ptr_vector.pop_back();
	}
}


void EntityManager::debugEntityInfo()
{
	std::cout << "==========debug entit info =================" << std::endl;

	std::cout << "Entityes = [ ";
	for(auto const& ent: entities_)
	{
		std::cout << "(" << ent->debugInfo() << "," << ent << " ) ," ;
	}
	std::cout << "]" << std::endl;


	std::cout << "CompEntities = { " << std::endl;
	for(auto const& kv: comp_entities_)
	{
		std::cout << kv.first << " : [" ;
		for(auto const& ent: kv.second)
		{
			std::cout << "(" << ent->debugInfo() << "," << ent << " ) ," ;
		}
		std::cout << "]" << std::endl;
	}
	std::cout << " } " << std::endl;
	std::cout << "=============================================" << std::endl;
}
}//ecs
