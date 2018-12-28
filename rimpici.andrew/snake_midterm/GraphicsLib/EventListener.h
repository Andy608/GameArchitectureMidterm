/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#ifndef EVENT_LISTENER_H_
#define EVENT_LISTENER_H_

#include <Trackable.h>
#include "Event.h"

class EventSystem;

class EventListener : public Trackable
{
public:
	EventListener( EventSystem* pEventSystem );
	virtual ~EventListener();

	virtual void handleEvent( const Event& theEvent ) = 0;

protected:
	EventSystem* getEventSystem() const { return mpEventSystem; };

private:
	EventSystem* mpEventSystem; //the event system this lister is listening to
};

#endif