/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#ifndef EVENT_MOUSE_INPUT_H_
#define EVENT_MOUSE_INPUT_H_

#include "Event.h"
#include <Vector2D.h>

class EventMouseInput : public Event
{
public:
	static const EventType sEVENT_ID;

	EventMouseInput(int inputCode, bool isPressed, int xPosition, int yPosition);
	virtual ~EventMouseInput();

	inline const int& getInputCode() const { return mInputCode; };
	inline const bool& justPressed() const { return mIsPressed; };
	inline const Vector2D& getMousePosition() const { return mMousePosition; };

private:
	int mInputCode;
	bool mIsPressed;
	Vector2D mMousePosition;
};

#endif