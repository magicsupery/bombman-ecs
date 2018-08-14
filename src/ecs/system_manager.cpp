#include "system_manager.h"
#include "system.h"

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

void SystemManager::addSystem(SystemPtr system_ptr)
{
	tick_systems_.insert(system_ptr);
}

void SystemManager::removeSystem(SystemPtr system_ptr)
{
	auto it = tick_systems_.find(system_ptr);
	if(it != tick_systems_.end())
		tick_systems_.erase(it);
}

void SystemManager::tick(float dt)
{
	for(auto const& v: tick_systems_)
		v->tick(dt);
}
