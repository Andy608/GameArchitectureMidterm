/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "InputSystem.h"
#include <allegro5/allegro.h>
#include "System.h"
#include "EventSystem.h"
#include "EventKeyboardInput.h"
#include "EventMouseInput.h"
#include "EventWindowClosed.h"

InputSystem::InputSystem() :
	mIsInitialized( false )
{

}

InputSystem::~InputSystem()
{
	cleanup();
}


bool InputSystem::init()
{
	if ( !mIsInitialized )
	{
		mIsInitialized = true;

		mpEventQueue = al_create_event_queue();

		if ( !mpEventQueue )
		{
			std::cout << "Failed to create event queue." << std::endl;
			cleanup();
		}
		else if ( !al_install_mouse() )
		{
			std::cout << "Failed to install mouse input." << std::endl;
			cleanup();
		}
		else if ( !al_install_keyboard() )
		{
			std::cout << "Failed to install keyboard input." << std::endl;
			cleanup();
		}
		else
		{
			al_register_event_source( mpEventQueue, al_get_display_event_source( GraphicsSystem::getInstance()->mpDisplay ) );
			al_register_event_source( mpEventQueue, al_get_mouse_event_source() );
			al_register_event_source( mpEventQueue, al_get_keyboard_event_source() );
		}
	}

	return mIsInitialized;
}

void InputSystem::cleanup()
{
	if ( mIsInitialized )
	{
		al_uninstall_keyboard();
		al_uninstall_mouse();

		mIsInitialized = false;
	}
}

void InputSystem::update(float deltaTime)
{
	ALLEGRO_EVENT evnt;

	while (al_get_next_event(mpEventQueue, &evnt))
	{
		//Event from Allegro Event Queue
		switch (evnt.type)
		{
		case ALLEGRO_EVENT_KEY_DOWN:
			//New keydown event
			EventSystem::getInstance()->fireEvent(EventKeyboardInput( evnt.keyboard.keycode, true ) );
			break;
		case ALLEGRO_EVENT_KEY_UP:
			//New keyup event
			EventSystem::getInstance()->fireEvent(EventKeyboardInput( evnt.keyboard.keycode, false ) );
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			EventSystem::getInstance()->fireEvent( EventMouseInput( evnt.mouse.button, true, evnt.mouse.x, evnt.mouse.y ) );
			//New mouse button down event
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			EventSystem::getInstance()->fireEvent( EventMouseInput( evnt.mouse.button, false, evnt.mouse.x, evnt.mouse.y) );
			//New mouse button up event
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			EventSystem::getInstance()->fireEvent( EventWindowClosed() );
			//New display close event
			break;
		}
	}
}

ALLEGRO_EVENT_QUEUE* InputSystem::getEventQueue() const
{
	return mpEventQueue;
}

Vector2D InputSystem::getMousePosition() const
{
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);

	return Vector2D(mouseState.x, mouseState.y);
}