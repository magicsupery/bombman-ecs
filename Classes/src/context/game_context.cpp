#include "game_context.h"
#include "../helper/utils.hpp"

namespace ecs
{
EntityPtr GameContext::input_p1= nullptr;

std::time_t GameContext::last_tick_time = getTimeStamp();

cocos2d::Scene* GameContext::running_scene = nullptr;

uint64_t GameContext::keybord_bit = 0x0;

KeyboardCodeVector GameContext::move_keyboardcode_vector;

} //ecs
