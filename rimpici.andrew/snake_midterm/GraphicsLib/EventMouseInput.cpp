/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "EventMouseInput.h"
#include "InputSystem.h"

const EventType EventMouseInput::sEVENT_ID = "Mouse Input Event";

EventMouseInput::EventMouseInput(int inputCode, bool isPressed, int xPosition, int yPosition) :
	Event(sEVENT_ID),
	mInputCode(inputCode),
	mIsPressed(isPressed),
	mMousePosition(Vector2D(xPosition, yPosition))
{

}

EventMouseInput::~EventMouseInput()
{

}