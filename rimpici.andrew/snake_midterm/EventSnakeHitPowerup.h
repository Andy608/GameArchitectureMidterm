#ifndef EVENT_SNAKE_HIT_POWERUP_H_
#define EVENT_SNAKE_HIT_POWERUP_H_

#include <Event.h>

class EventSnakeHitPowerup : public Event
{
public:
	static const std::string sEVENT_ID;

	EventSnakeHitPowerup();
	virtual ~EventSnakeHitPowerup();
};

#endif