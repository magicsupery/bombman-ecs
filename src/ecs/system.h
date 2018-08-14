#ifndef _H_SYSTEM_H_
#define _H_SYSTEM_H_

class System
{
public:
	System() = default;
	~System() = default;
	System(const System& other) = delete;
	System& operator = (const System& other) = delete ;

	virtual void tick(float dt) = 0;
};
#endif
