#include "controller.hpp"
#include "../helper/const.hpp"
namespace ecs
{
Component::CompType Controller::comp_id = COMPONENT_ID_CONTROLLER;

void Controller::addOp(ControllerOp op, ControllerOpData op_data)
{
	auto it = op_map_.find(op);
	if(it == op_map_.end())
		op_map_[op] = 0;

	op_map_[op] |= op_data;
}

void Controller::clearOp(ControllerOp op)
{
	op_map_[op] = 0;
}

} //ecs
