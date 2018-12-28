/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "EventSystem.h"
#include "Event.h"
#include "EventListener.h"
#include <assert.h>

EventSystem* EventSystem::smpInstance = nullptr;

EventSystem* EventSystem::getInstance()
{
	assert( smpInstance );
	return smpInstance;
}

void EventSystem::initInstance()
{
	if ( !smpInstance )
	{
		smpInstance = new EventSystem();
	}
}

void EventSystem::cleanupInstance()
{
	if ( smpInstance )
	{
		delete smpInstance;
		smpInstance = nullptr;
	}
}

EventSystem::EventSystem()
{

}

EventSystem::~EventSystem()
{

}

void EventSystem::addListener( std::string type, EventListener* pListener )
{
	smpInstance->mListenerMap.insert( std::pair< std::string, EventListener* >(type, pListener) );
}

void EventSystem::removeListener( std::string type, EventListener *pListener )
{
	std::pair<std::multimap<std::string, EventListener*>::iterator, std::multimap<std::string, EventListener*>::iterator> ret;

	ret = smpInstance->mListenerMap.equal_range( type );
	std::multimap<std::string, EventListener*>::iterator iter;

	for( iter = ret.first; iter != ret.second; ++iter )
	{
		if( iter->second == pListener )
		{
			smpInstance->mListenerMap.erase( iter );
			break;//to prevent using invalidated iterator
		}
	}
}

void EventSystem::removeListenerFromAllEvents( EventListener* pListener )
{
	std::multimap<std::string, EventListener*>::iterator iter;

	bool allTheWayThrough = false;

	while( !allTheWayThrough )
	{
		allTheWayThrough = true;
		for( iter = smpInstance->mListenerMap.begin(); iter != smpInstance->mListenerMap.end(); ++iter )
		{
			if( iter->second == pListener )
			{
				smpInstance->mListenerMap.erase( iter );
				allTheWayThrough = false; //didn't make it the whole way through
				break;//to prevent using invalidated iterator
			}
		}
	}
}

void EventSystem::fireEvent( const Event& theEvent )
{
	smpInstance->dispatchAllEvents( theEvent );
}

void EventSystem::dispatchAllEvents( const Event& theEvent )
{
	std::pair<std::multimap<std::string, EventListener*>::iterator, std::multimap<std::string, EventListener*>::iterator> ret;
	ret = smpInstance->mListenerMap.equal_range( theEvent.mEVENT_ID );

	std::multimap<std::string, EventListener*>::iterator iter;
	for( iter = ret.first; iter != ret.second; ++iter )
	{
		iter->second->handleEvent( theEvent );
	}

}