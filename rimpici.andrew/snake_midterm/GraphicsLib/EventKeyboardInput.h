/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#ifndef EVENT_KEYBOARD_INPUT_H_
#define EVENT_KEYBOARD_INPUT_H_

#include "Event.h"

class EventKeyboardInput : public Event
{
public:
	static const EventType sEVENT_ID;

	EventKeyboardInput( int inputCode, bool isPressed );
	virtual ~EventKeyboardInput();

	const int& getInputCode() const;
	const bool& isPressed() const;

private:
	bool mIsPressed;
	int mInputCode;
};

#endif