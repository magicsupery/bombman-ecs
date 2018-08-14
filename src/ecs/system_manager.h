#ifndef _H_SYSTEMMANAGER_H_
#define _H_SYSTEMMANAGER_H_

#include <set>

class System;
class SystemManager
{

using SystemPtr =
	std::shared_ptr<System> ;

using SystemPtrVecotr =
	std::set<SystemPtr>;

public:
	~SystemManager();
	SystemManager(const SystemManager&) = delete;
	SystemManager& operator = (const SystemManager& ) = delete;

private:
	SystemManager() = default;

public:
	static SystemManager* getInstance();
	void addSystem(SystemPtr system_ptr);
	void removeSystem(SystemPtr system_ptr);
	void tick(float dt);

private:
	static SystemManager* instance_;
	SystemPtrVecotr tick_systems_;
};
#endif
