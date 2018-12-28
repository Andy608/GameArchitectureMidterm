/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Event.h"

const EventType Event::sINVALID_EVENT_NAME = "Invalid Event Name";

Event::Event( EventType eventType ) :
	mEVENT_ID( eventType )
{

}

Event::~Event()
{

}