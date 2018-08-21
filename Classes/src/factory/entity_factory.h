#ifndef _H_ENTITYFACTORY_H_
#define _H_ENTITYFACTORY_H_

#include "../ecs/entity.hpp"
namespace ecs
{
class EntityFactory
{

public:
	~EntityFactory();
	EntityFactory(const EntityFactory&) = delete;
	EntityFactory& operator = (const EntityFactory& ) = delete;

public:
	static EntityFactory* getInstance();

public:
	EntityPtr createP1();

private:
	EntityFactory();
	static EntityFactory* instance_;

};
}//ecs
#endif

