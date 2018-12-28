/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Color.h"

Color::Color( unsigned char r, unsigned char g, unsigned char b, unsigned char a ) :
	red( r ),
	green( g ),
	blue( b ),
	alpha( a )
{

}

Color::Color( unsigned char r, unsigned char g, unsigned char b ) :
	Color( r, g, b, 255 )
{

}
