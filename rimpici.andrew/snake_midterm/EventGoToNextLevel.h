#ifndef EVENT_GO_TO_NEXT_LEVEL_H_
#define EVENT_GO_TO_NEXT_LEVEL_H_

#include <Event.h>

class EventGoToNextLevel : public Event
{
public:
	static const std::string sEVENT_ID;

	EventGoToNextLevel();
	virtual ~EventGoToNextLevel();
};

#endif