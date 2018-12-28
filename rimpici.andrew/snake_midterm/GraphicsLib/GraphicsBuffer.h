/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#ifndef GRAPHICS_BUFFER_H_
#define GRAPHICS_BUFFER_H_

#include <Trackable.h>

struct ALLEGRO_BITMAP;
struct Color;

class GraphicsBuffer : public Trackable
{
	friend class GraphicsSystem;

public:
	GraphicsBuffer( int width, int height, Color defaultColor );
	GraphicsBuffer( const std::string& imagePath );
	~GraphicsBuffer();

	const int& getWidth() const;
	const int& getHeight() const;

	const Color& getPixelColor(int x, int y) const;

private:
	GraphicsBuffer( ALLEGRO_BITMAP* pBitmap );
	ALLEGRO_BITMAP* mpBitmap;
	int mBitmapWidth;
	int mBitmapHeight;
	bool mOwnsBitmap;

	ALLEGRO_BITMAP* loadBitmap( const std::string& imagePath );
	int initWidth( ALLEGRO_BITMAP* pBitmap );
	int initHeight( ALLEGRO_BITMAP* pBitmap );
};

#endif