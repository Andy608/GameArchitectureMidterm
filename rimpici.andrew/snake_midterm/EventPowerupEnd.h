#ifndef EVENT_POWER_UP_END_H_
#define EVENT_POWER_UP_END_H_

#include <Event.h>

class EventPowerupEnd : public Event
{
public:
	static const std::string sEVENT_ID;

	EventPowerupEnd();
	virtual ~EventPowerupEnd();
};

#endif