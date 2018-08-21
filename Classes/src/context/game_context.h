#ifndef _H_GAMECONTEXT_H_
#define _H_GAMECONTEXT_H_
#include <chrono>

#include "../ecs/entity.hpp"
struct GameContext
{
	static EntityPtr input_p1;
	static std::time_t last_tick_time;
};

#endif

