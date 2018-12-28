#ifndef EVENT_SNAKE_HIT_SELF_H_
#define EVENT_SNAKE_HIT_SELF_H_

#include <Event.h>

class EventSnakeHitSelf : public Event
{
public:
	static const std::string sEVENT_ID;

	EventSnakeHitSelf();
	virtual ~EventSnakeHitSelf();
};

#endif