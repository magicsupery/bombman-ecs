#ifndef _H_CONTROLLER_H_
#define _H_CONTROLLER_H_
#include "../ecs/system.h"

class ControllerSystem: public System
{
public:
	virtual void tick(float dt);
	virtual SystemType getSystemId() {return ControllerSystem::system_id;}
	static SystemType system_id;
};
#endif

