/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Sprite.h"

Sprite::Sprite( const GraphicsBuffer& spriteBuffer, const int startingX, const int startingY, const int width, const int height ) :
	mSPRITE_BUFFER( spriteBuffer ),
	mSTARTING_X( startingX ),
	mSTARTING_Y( startingY ),
	mWIDTH( width ),
	mHEIGHT( height )
{

}

Sprite::~Sprite()
{

}

const int& Sprite::getStartingX() const
{
	return mSTARTING_X;
}

const int& Sprite::getStartingY() const
{
	return mSTARTING_Y;
}

const int& Sprite::getWidth() const
{
	return mWIDTH;
}

const int& Sprite::getHeight() const
{
	return mHEIGHT;
}