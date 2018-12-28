#ifndef EVENT_SNAKE_NORTH_H_
#define EVENT_SNAKE_NORTH_H_

#include <Vector2D.h>
#include <Event.h>
#include "Snake.h"
#include <string>

enum EnumDirection;

class EventSnakeDirection : public Event
{
public:
	static const std::string sEVENT_ID;
	static const std::string sEVENT_ID_UP;
	static const std::string sEVENT_ID_RIGHT;
	static const std::string sEVENT_ID_DOWN;
	static const std::string sEVENT_ID_LEFT;

	EventSnakeDirection(EnumDirection snakeDirection);
	virtual ~EventSnakeDirection();

	inline EnumDirection getDirection() const { return mSnakeDirection; };

private:
	static const std::string& getDirectionID(EnumDirection snakeDirection);

	EnumDirection mSnakeDirection;
};

#endif