#include "Powerup.h"
#include <Animation.h>
#include <GraphicsSystem.h>
#include "EventPowerupEnd.h"
#include <EventSystem.h>
#include "Snake.h"
#include "Level.h"

Powerup::Powerup(EnumItem type, int duration, Animation* pAnimation, Vector2D position, Level* level) :
	Item(pAnimation, position),
	mType(type),
	mDURATION(duration),
	mLevel(level)
{

}

Powerup::~Powerup()
{

}

void Powerup::update(float deltaTime)
{
	if (mIsActive)
	{
		mDurationCounter += deltaTime;
		if (mDurationCounter >= mDURATION)
		{
			mIsActive = false;
			mDurationCounter = 0;
			mLevel->mpSnake->mMovementSpeed = mLevel->mSTART_SPEED;
		}
	}

	Item::update(deltaTime);
}