#ifndef _HPP_COMPONENT_H_
#define _HPP_COMPONENT_H_
#include <string>

namespace ecs
{
class Component
{

public:
	using CompType =
		int;

public:
	Component() = default;
	~Component() = default;
	Component(const Component& other) = delete;
	Component& operator = (const Component& other) = delete ;

	virtual std::string name() = 0;

	virtual CompType getCompId() = 0;

	static CompType comp_id;
};
} //ecs
#endif
