#ifndef _H_CONTROLLER_HPP_
#define _H_CONTROLLER_HPP_
#include <unordered_map>
#include <vector>

#include "../ecs/component.h"
#include "../helper/utils.hpp"


/*
 * 用于记录当前的控制器操作
 * 通过键盘输入或者网络输入改变controller的操作
 * 最终通过controllersystem去影响对应的component
 */
enum ControllerOp
{
	Move,
	Skill,
};

enum ControllerOpData
{
	Up = 0x1,
	Down = 0x2,
	Left = 0x4,
	Rigth = 0x8,
	SkillActiveOne = 0x10,
};

// 这里可以进行优化，不需要vector记录，因为该游戏，不需要搓招，所以通过比特为记录操作即可，
// 并且可以通过特定的值查看是否有互斥操作

using OpMap =
	BoomUnorderedMap<ControllerOp, uint64_t>;

class Controller: public Component
{
public:
	void addOp(ControllerOp op, ControllerOpData op_data);
	OpMap op_map_;

public:

	virtual std::string name() {return "Controller";}
	virtual Component::CompType getCompId() {return Controller::comp_id;}
	static Component::CompType comp_id;
};
#endif

