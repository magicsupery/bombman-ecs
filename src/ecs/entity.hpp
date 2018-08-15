#ifndef _HPP_ENTITY_HPP_
#define _HPP_ENTITY_HPP_
#include <memory>
#include <map>
#include <vector>

#include "component.h"

class Entity: public std::enable_shared_from_this<Entity>
{
using ComponentMap =
	std::map<Component::CompType, std::shared_ptr<Component> >;
using ComponentIdxMap =
	std::map<Component::CompType, int>;

public:
	Entity();
	~Entity();
	Entity(const Entity&) = delete;
	Entity& operator= (const Entity&) = delete;

public:
	void addComponent(std::shared_ptr<Component> comp);
	void removeComponent(Component::CompType comp_id);

	template<typename T>
	std::shared_ptr<T> getComponent()
	{

		auto it = component_map_.find(T::comp_id);
		if(it != component_map_.end())
		{
			return std::static_pointer_cast<T>(it->second);
		}

		return nullptr;
	}

	std::vector<Component::CompType> getComponentIds();
public:

	inline void set_idx(int idx)
	{
		idx_ = idx;
	}
	inline int get_idx()
	{
		return idx_;
	}

	inline void clear_idx()
	{
		idx_ = -1;
	}

	inline void set_comp_idx(Component::CompType comp_id, int idx)
	{
		component_idx_map_[comp_id] = idx;
	}

	inline int get_comp_idx(Component::CompType comp_id)
	{
		return component_idx_map_[comp_id];
	}

public:
	std::string debugInfo();
public:
	int id;
private:
	ComponentMap component_map_;

	// 为了方便的remove，每个entity记录着自己的idx以及相关的comp_id对应的idx
	// idx_ == -1 的时，证明entity未被manager管理
	int idx_;
	ComponentIdxMap component_idx_map_;

};

using EntityPtr =
	std::shared_ptr<Entity>;

#endif
