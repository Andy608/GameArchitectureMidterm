/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "EventWindowClosed.h"

const EventType EventWindowClosed::sEVENT_ID = "Window Closed Event";

EventWindowClosed::EventWindowClosed() :
	Event( sEVENT_ID )
{

}

EventWindowClosed::~EventWindowClosed()
{

}