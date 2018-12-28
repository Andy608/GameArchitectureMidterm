#ifndef EVENT_SNAKE_HIT_FOOD_H_
#define EVENT_SNAKE_HIT_FOOD_H_

#include <Event.h>

class EventSnakeHitFood : public Event
{
public:
	static const std::string sEVENT_ID;

	EventSnakeHitFood();
	virtual ~EventSnakeHitFood();
};

#endif