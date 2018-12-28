/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#ifndef EVENT_SYSTEM_H_
#define EVENT_SYSTEM_H_

#include <map>
#include <Trackable.h>

class EventListener;
class Event;

class EventSystem : public Trackable
{
public:
	static EventSystem* getInstance();
	static void initInstance();
	static void cleanupInstance();

	//Disable any form of copying for a EventSystem object.
	EventSystem( const EventSystem& copy ) = delete;
	void operator=( const EventSystem& copy ) = delete;

	static void fireEvent( const Event& theEvent );
	static void addListener( std::string type, EventListener* pListener );
	static void removeListener( std::string type, EventListener* pListener );
	static void removeListenerFromAllEvents( EventListener* pListener );

private:
	static EventSystem* smpInstance;

	std::multimap< std::string, EventListener* > mListenerMap;

	EventSystem();
	~EventSystem();

	void dispatchAllEvents( const Event& theEvent );
};

#endif