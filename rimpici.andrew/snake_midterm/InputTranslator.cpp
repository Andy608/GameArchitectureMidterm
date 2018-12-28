/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "InputTranslator.h"
#include <EventSystem.h>
#include "EventSnakeDirection.h"
#include <EventWindowClosed.h>
#include <EventMouseInput.h>
#include <EventKeyboardInput.h>
#include <System.h>
#include <InputSystem.h>

InputTranslator::InputTranslator() :
	EventListener( EventSystem::getInstance() )
{

}

InputTranslator::~InputTranslator()
{
	cleanup();
}

bool InputTranslator::init()
{
	if ( !mIsInitialized )
	{
		mIsInitialized = true;

		EventSystem::addListener( EventKeyboardInput::sEVENT_ID, this );
		EventSystem::addListener( EventMouseInput::sEVENT_ID, this );

		mInputMap.insert(std::make_pair(EnumKeyInput::ESCAPE_KEY, EventWindowClosed::sEVENT_ID));

		mInputMap.insert(std::make_pair(EnumKeyInput::UP_KEY, EventSnakeDirection::sEVENT_ID_UP));
		mInputMap.insert(std::make_pair(EnumKeyInput::DOWN_KEY, EventSnakeDirection::sEVENT_ID_DOWN));
		mInputMap.insert(std::make_pair(EnumKeyInput::RIGHT_KEY, EventSnakeDirection::sEVENT_ID_RIGHT));
		mInputMap.insert(std::make_pair(EnumKeyInput::LEFT_KEY, EventSnakeDirection::sEVENT_ID_LEFT));
	}

	return mIsInitialized;
}

void InputTranslator::cleanup()
{
	if ( mIsInitialized )
	{
		EventSystem::removeListener( EventKeyboardInput::sEVENT_ID, this );
		EventSystem::removeListener( EventMouseInput::sEVENT_ID, this );
	}
}

EventType InputTranslator::getEventFromMapping( int originalMapping )
{
	EventType eventValue = Event::sINVALID_EVENT_NAME;

	std::map<int, EventType>::iterator iter = mInputMap.find( originalMapping );

	if ( iter != mInputMap.end() )
	{
		eventValue = iter->second;
	}

	return eventValue;
}

void InputTranslator::handleEvent( const Event& theEvent )
{
	if ( theEvent.mEVENT_ID.compare( EventKeyboardInput::sEVENT_ID ) == 0 )
	{
		const EventKeyboardInput& inputEvent = static_cast<const EventKeyboardInput&>( theEvent );

		EventType translatedEventType = getEventFromMapping( inputEvent.getInputCode() );

		if (translatedEventType.compare(EventSnakeDirection::sEVENT_ID_UP) == 0)
		{
			if (inputEvent.isPressed())
			{
				fireTranslatedEvent(EventSnakeDirection(EnumDirection::NORTH));
			}
		}
		else if (translatedEventType.compare(EventSnakeDirection::sEVENT_ID_DOWN) == 0)
		{
			if (inputEvent.isPressed())
			{
				fireTranslatedEvent(EventSnakeDirection(EnumDirection::SOUTH));
			}
		}
		else if (translatedEventType.compare(EventSnakeDirection::sEVENT_ID_RIGHT) == 0)
		{
			if (inputEvent.isPressed())
			{
				fireTranslatedEvent(EventSnakeDirection(EnumDirection::EAST));
			}
		}
		else if (translatedEventType.compare(EventSnakeDirection::sEVENT_ID_LEFT) == 0)
		{
			if (inputEvent.isPressed())
			{
				fireTranslatedEvent(EventSnakeDirection(EnumDirection::WEST));
			}
		}
		else if ( translatedEventType.compare( EventWindowClosed::sEVENT_ID ) == 0 )
		{
			if ( inputEvent.isPressed() )
			{
				fireTranslatedEvent( EventWindowClosed() );
			}
		}
	}
}

void InputTranslator::fireTranslatedEvent( const Event& theEvent )
{
	EventSystem::fireEvent( theEvent );
}