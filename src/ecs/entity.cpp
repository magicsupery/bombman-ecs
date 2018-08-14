#include "entity.hpp"
#include "entity_manager.h"
#include "component.h"

#include <iostream>

Entity::Entity():
	idx_(-1)
{
}

Entity::~Entity()
{
	component_map_.clear();
	component_idx_map_.clear();
}

void Entity::addComponent(std::shared_ptr<Component> comp)
{
	auto comp_id = comp->getCompId();
	component_map_[comp_id] = comp;
	if(idx_ != -1)
		EntityManager::getInstance()->notifyAddComponent(shared_from_this(), comp_id);
}

void Entity::removeComponent(Component::CompType comp_id)
{
	auto it = component_map_.find(comp_id);
	if(it != component_map_.end())
	{
		component_map_.erase(it);

		if(idx_ != -1)
			EntityManager::getInstance()->notifyRemoveComponent(shared_from_this(), comp_id);
	}
	return;
}

std::vector<Component::CompType> Entity::getComponentIds()
{
	std::vector<Component::CompType> v;
	for(auto const& kv  : component_map_)
	{
		v.emplace_back(kv.first);
	}

	return v;
}


std::string Entity::debugInfo()
{
	std::string res;

	res+= "EntityInfo(";
	for(auto const& kv: component_map_)
	{
		res += kv.second->name();
		res += "|";
	}
	res += ")";

	return res;
}
