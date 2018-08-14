#ifndef _H_ENTITYMANAGER_H_
#define _H_ENTITYMANAGER_H_
#include <vector>
#include <map>

#include "entity.hpp"

class EntityManager
{
using EntityPtr =
	std::shared_ptr<Entity>;

using EntityPtrVecotrPtr =
	std::shared_ptr<std::vector<EntityPtr> >;
public:
	~EntityManager();
	EntityManager(const EntityManager&) = delete;
	EntityManager& operator = (const EntityManager& ) = delete;

public:
	static EntityManager* getInstance();

	void addEntity(EntityPtr ent_ptr);
	void removeEntity(EntityPtr ent_ptr);
	EntityPtrVecotrPtr  getEntitiesByComp(Component::CompType comp_id);

	void debugEntityInfo();
public:
	void notifyAddComponent(EntityPtr ent_ptr, Component::CompType comp_id);
	void notifyRemoveComponent(EntityPtr ent_ptr, Component::CompType comp_id);

private:
	EntityManager();
	static EntityManager* instance_;

private:
	// all ents
	std::vector<EntityPtr > entities_;

	// ents who has comps
	std::map<Component::CompType, std::vector<EntityPtr> > comp_entities_;
};

#endif
