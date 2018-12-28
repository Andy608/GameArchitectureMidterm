/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#ifndef COLOR_H_
#define COLOR_H_

#include <Trackable.h>

struct Color : public Trackable
{
	friend class GraphicsSystem;
	friend class GraphicsBuffer;

	Color( unsigned char r, unsigned char g, unsigned char b, unsigned char a );
	Color( unsigned char r, unsigned char g, unsigned char b );

	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;
};

#endif