#ifndef _H_SYSTEM_H_
#define _H_SYSTEM_H_

namespace ecs
{
class System
{
public:
	using SystemType =
		int;
public:
	System() = default;
	~System() = default;
	System(const System& other) = delete;
	System& operator = (const System& other) = delete ;

	virtual void tick(float dt) = 0;

	virtual SystemType getSystemId() = 0;
public:
	static SystemType system_id;

};
} // ecs
#endif
