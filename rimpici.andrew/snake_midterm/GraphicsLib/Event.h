/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#ifndef EVENT_H_
#define EVENT_H_

#include <string>
#include <Trackable.h>
#include <vector>

typedef std::string EventType;

class Event : public Trackable
{
public:
	static const EventType sINVALID_EVENT_NAME;
	
	const EventType mEVENT_ID;

	Event( EventType eventType );
	virtual ~Event() = 0;
};

#endif