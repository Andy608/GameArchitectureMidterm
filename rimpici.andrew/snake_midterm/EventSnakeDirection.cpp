#include "EventSnakeDirection.h"

const std::string EventSnakeDirection::sEVENT_ID = "Snake Direction Event";
const std::string EventSnakeDirection::sEVENT_ID_UP = "Snake Direction Event Up";
const std::string EventSnakeDirection::sEVENT_ID_RIGHT = "Snake Direction Event Right";
const std::string EventSnakeDirection::sEVENT_ID_DOWN = "Snake Direction Event Down";
const std::string EventSnakeDirection::sEVENT_ID_LEFT = "Snake Direction Event Left";

EventSnakeDirection::EventSnakeDirection(EnumDirection snakeDirection) :
	Event(sEVENT_ID),
	mSnakeDirection(snakeDirection)
{

}

EventSnakeDirection::~EventSnakeDirection()
{

}

const std::string& EventSnakeDirection::getDirectionID(EnumDirection snakeDirection)
{
	switch (snakeDirection)
	{
	case EnumDirection::NORTH:
		return sEVENT_ID_UP;
	case EnumDirection::SOUTH:
		return sEVENT_ID_DOWN;
	case EnumDirection::EAST:
		return sEVENT_ID_RIGHT;
	case EnumDirection::WEST:
		return sEVENT_ID_LEFT;
	}
}