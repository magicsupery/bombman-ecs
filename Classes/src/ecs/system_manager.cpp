#include "system_manager.h"
#include "system.h"

namespace ecs
{
SystemManager* SystemManager::instance_ = nullptr;

SystemManager::~SystemManager()
{
	tick_systems_.clear();
}

SystemManager* SystemManager::getInstance()
{
	if(instance_ == nullptr)
		instance_ = new SystemManager();

	return instance_;
}

void SystemManager::tick(float dt)
{
	for(auto const& v: tick_systems_)
		v->tick(dt);
}

}
