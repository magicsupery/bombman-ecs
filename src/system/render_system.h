#ifndef _H_RENDERSYSTEM_H_
#define _H_RENDERSYSTEM_H_

#include "../ecs/system.h"

class RenderSystem : public System
{
public:
	virtual void tick(float dt);
};

#endif

