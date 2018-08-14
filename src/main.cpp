#include <memory>
#include <iostream>
#include <thread>

#include "ecs/entity_manager.h"
#include "ecs/system_manager.h"
#include "ecs/entity.hpp"

#include "component/transform.hpp"
#include "component/moveable.hpp"

#include "system/move_system.h"
#include "system/render_system.h"


void test1();

void test2();

int main()
{
	//test1();
	test2();
}


void test2()
{

	auto entity_ptr = std::make_shared<Entity>();
	auto comp_ptr = std::make_shared<Transform>();
	comp_ptr->pos_x = 10;
	entity_ptr->addComponent(comp_ptr);

	auto comp_ptr_2 = std::make_shared<Moveable>();
	comp_ptr_2->speed = 1;
	comp_ptr_2->derection = 1;
	entity_ptr->addComponent(comp_ptr_2);

	EntityManager::getInstance()->addEntity(entity_ptr);


	SystemManager::getInstance()->addSystem(std::make_shared<MoveSystem>());
	SystemManager::getInstance()->addSystem(std::make_shared<RenderSystem>());
	while(true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
		SystemManager::getInstance()->tick(30);
	}
}
void test1()
{
	auto entity_ptr = std::make_shared<Entity>();
	auto comp_ptr = std::make_shared<Transform>();
	comp_ptr->pos_x = 10;
	entity_ptr->addComponent(comp_ptr);

	EntityManager::getInstance()->addEntity(entity_ptr);

	EntityManager::getInstance()->debugEntityInfo();

	auto entity_ptr_2 = std::make_shared<Entity>();
	EntityManager::getInstance()->addEntity(entity_ptr_2);
	auto comp_ptr_2 = std::make_shared<Moveable>();
	entity_ptr_2->addComponent(comp_ptr_2);
	entity_ptr_2->addComponent(std::make_shared<Transform>());
	EntityManager::getInstance()->debugEntityInfo();

	EntityManager::getInstance()->removeEntity(entity_ptr_2);
	EntityManager::getInstance()->debugEntityInfo();
}
