/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include <MemoryTracker.h>
#include <EventSystem.h>
#include "Game.h"

using namespace std;

int main()
{
	const int DISPLAY_WIDTH  = 1024;
	const int DISPLAY_HEIGHT = 576;

	EventSystem::initInstance();
	Game::initInstance();
	Game::getInstance()->init( DISPLAY_WIDTH, DISPLAY_HEIGHT );

	Game::getInstance()->loop();
	Game::cleanupInstance();
	EventSystem::cleanupInstance();

	gMemoryTracker.reportAllocations( cout );

	system("pause");
	return 0;

}