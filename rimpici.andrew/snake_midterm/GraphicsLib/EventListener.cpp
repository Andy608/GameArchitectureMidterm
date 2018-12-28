/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "EventListener.h"
#include "EventSystem.h"

EventListener::EventListener( EventSystem* pEventSystem ) :
	mpEventSystem( pEventSystem )
{

}

EventListener::~EventListener()
{
	mpEventSystem->removeListenerFromAllEvents( this );
}
