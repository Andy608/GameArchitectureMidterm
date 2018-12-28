/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "EventKeyboardInput.h"
#include "InputSystem.h"

const EventType EventKeyboardInput::sEVENT_ID = "Keyboard Input Event";

EventKeyboardInput::EventKeyboardInput( int inputCode, bool isPressed ) :
	Event( sEVENT_ID ),
	mInputCode( inputCode ),
	mIsPressed( isPressed )
{

}

EventKeyboardInput::~EventKeyboardInput()
{

}

const int& EventKeyboardInput::getInputCode() const
{
	return mInputCode;
}

const bool& EventKeyboardInput::isPressed() const
{
	return mIsPressed;
}