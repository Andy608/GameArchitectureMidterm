#ifndef EVENT_SNAKE_HIT_WALL_H_
#define EVENT_SNAKE_HIT_WALL_H_

#include <Event.h>

class EventSnakeHitWall : public Event
{
public:
	static const std::string sEVENT_ID;

	EventSnakeHitWall();
	virtual ~EventSnakeHitWall();
};

#endif