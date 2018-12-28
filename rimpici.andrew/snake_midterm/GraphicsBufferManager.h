/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#ifndef GRAPHICS_BUFFER_MANAGER_H_
#define GRAPHICS_BUFFER_MANAGER_H_

#include <Trackable.h>
#include <map>
#include <string>
#include <GraphicsBuffer.h>

class GraphicsBufferManager : public Trackable
{
public:
	GraphicsBufferManager( const GraphicsBuffer& displayBuffer );
	~GraphicsBufferManager();

	bool addBuffer( std::string bufferKey, GraphicsBuffer* pBuffer );
	GraphicsBuffer* getBuffer( std::string bufferKey ) const;

	bool deleteBuffer( std::string bufferKey );

	void clearBuffers();

private:
	std::map<std::string, GraphicsBuffer*> mBufferMap;
	const GraphicsBuffer& mDisplayBuffer;
};

#endif