/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#ifndef SPRITE_SHEET_H_
#define SPRITE_SHEET_H_

#include <Trackable.h>
#include <vector>

class GraphicsBuffer;
class Sprite;

class SpriteSheet : public Trackable
{
public:
	SpriteSheet( const GraphicsBuffer& spriteSheetBuffer, unsigned int rows, unsigned int columns, unsigned int spriteWidths, unsigned int spriteHeights );
	~SpriteSheet();

	const std::vector<Sprite*>& getSprites() const;

private:
	const GraphicsBuffer& mSPRITESHEET_BUFFER;
	const unsigned int mROWS;
	const unsigned int mCOLUMNS;
	const unsigned int mSPRITE_WIDTHS;
	const unsigned int mSPRITE_HEIGHTS;

	std::vector<Sprite*> mSprites;
};

#endif