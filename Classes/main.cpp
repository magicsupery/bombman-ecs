#include <memory>
#include <iostream>
#include <thread>
#include <random>
#include <array>

#include "ecs/entity_manager.h"
#include "ecs/system_manager.h"
#include "ecs/entity.hpp"

#include "component/transform.hpp"
#include "component/moveable.hpp"
#include "component/controller.hpp"

#include "system/move_system.h"
#include "system/render_system.h"
#include "system/controller_system.h"

#include "context/game_context.h"

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
	comp_ptr_2->speed_x = 0;
	comp_ptr_2->speed_y = 0;
	comp_ptr_2->speed = 0.01;
	entity_ptr->addComponent(comp_ptr_2);

	auto comp_ptr_3 = std::make_shared<Controller>();
	entity_ptr->addComponent(comp_ptr_3);

	EntityManager::getInstance()->addEntity(entity_ptr);

	GameContext::input_p1= entity_ptr;

	std::default_random_engine e;
	std::uniform_int_distribution<unsigned>u (0,3);
	std::array<ControllerOpData, 4> ops = {
		ControllerOpData::Left,
		ControllerOpData::Rigth,
		ControllerOpData::Up,
		ControllerOpData::Down};

	while(true)
	{
		//随机数来给player增加操作
		auto idx =u(e);
		GameContext::input_p1->getComponent<Controller>()->addOp(ControllerOp::Move, ops[idx]);

		if(idx % 2 == 0)
		{
			idx =u(e);
			GameContext::input_p1->getComponent<Controller>()->addOp(ControllerOp::Move, ops[idx]);
		}

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
