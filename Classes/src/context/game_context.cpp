#include "game_context.h"
#include "../helper/utils.hpp"

EntityPtr GameContext::input_p1= nullptr;

std::time_t GameContext::last_tick_time = getTimeStamp();
