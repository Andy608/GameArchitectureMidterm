/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#ifndef EVENT_WINDOW_CLOSED_H_
#define EVENT_WINDOW_CLOSED_H_

#include "Event.h"

class EventWindowClosed : public Event
{
public:
	static const EventType sEVENT_ID;

	EventWindowClosed();
	virtual ~EventWindowClosed();
};

#endif