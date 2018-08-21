#ifndef _H_SYSTEMMANAGER_H_
#define _H_SYSTEMMANAGER_H_

#include <unordered_map>
#include <vector>

#include "system.h"

class SystemManager
{

using SystemPtr =
	std::shared_ptr<System> ;

using SystemPtrVecotr =
	std::vector<SystemPtr>;

using SystemPtrMap =
	std::unordered_map<System::SystemType, SystemPtr>;
public:
	~SystemManager();
	SystemManager(const SystemManager&) = delete;
	SystemManager& operator = (const SystemManager& ) = delete;

private:
	SystemManager() = default;

public:
	static SystemManager* getInstance();
	void addSystem(SystemPtr system_ptr);


	template<typename T>
	inline std::shared_ptr<T> getSystem()
	{
		auto system_id = T::system_id;
		if(system_map_.find(system_id) == system_map_.end())
			return nullptr;

		return std::static_pointer_cast<T>(system_map_[system_id]);
	}

	//add remove must be called when tick is not triggered
	//otherwise iterator will go wrong!!!
	template<typename T>
	inline void addSystem()
	{
		auto system_id = T::system_id;
		if(system_map_.find(system_id) != system_map_.end())
			return;

		auto system_ptr = std::make_shared<T>();
		system_map_[system_id] = system_ptr;
		tick_systems_.emplace_back(system_ptr);
	}

	template<typename T>
	inline void removeSystem()
	{
		auto it = system_map_.find(T::system_id);
		if(it != system_map_.end())
		{
			auto system_ptr = system_map_[T::system_id];
			system_map_.erase(it);

			//remove from vector
			for(auto it = tick_systems_.begin(); it != tick_systems_.end(); it++)
			{
				if(*it == system_ptr)
				{
					tick_systems_.erase(it);
					return;
				}
			}
		}
	}

public:
	void tick(float dt);

private:
	static SystemManager* instance_;
	SystemPtrVecotr tick_systems_;
	SystemPtrMap system_map_;
};
#endif
