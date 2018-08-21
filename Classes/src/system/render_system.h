#ifndef _H_RENDERSYSTEM_H_
#define _H_RENDERSYSTEM_H_

#include "../ecs/system.h"

class RenderSystem : public System
{
public:
	virtual void tick(float dt);
	virtual SystemType getSystemId() {return RenderSystem::system_id;}
	static SystemType system_id;
};

#endif

