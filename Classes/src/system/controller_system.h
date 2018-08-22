#ifndef _H_CONTROLLER_H_
#define _H_CONTROLLER_H_
#include "../ecs/system.h"

namespace  ecs
{
class ControllerSystem: public System
{
public:
	virtual void tick(float dt);
	virtual SystemType getSystemId() {return ControllerSystem::system_id;}
	static SystemType system_id;

public:
	void notify_keyboard_move_event_changed();
	void notify_keyboard_skill_event_changed();
};
} //ecs
#endif

