/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "GraphicsBufferManager.h"

GraphicsBufferManager::GraphicsBufferManager( const GraphicsBuffer& displayBuffer ) :
	mBufferMap( std::map<std::string, GraphicsBuffer*>() ),
	mDisplayBuffer( displayBuffer )
{

}

GraphicsBufferManager::~GraphicsBufferManager()
{
	clearBuffers();
}

bool GraphicsBufferManager::addBuffer( std::string bufferKey, GraphicsBuffer* pBuffer )
{
	bool success = true;

	if ( !mBufferMap.insert(std::make_pair(bufferKey, pBuffer)).second )
	{
		std::cout << "Already implemented!" << std::endl;
		delete pBuffer;
		success = false;
	}

	return success;
}

GraphicsBuffer* GraphicsBufferManager::getBuffer( std::string bufferKey ) const
{
	GraphicsBuffer* foundBuffer = nullptr;
	auto iter = mBufferMap.find( bufferKey );

	if ( iter != mBufferMap.end() )
	{
		foundBuffer = iter->second;
	}
	else
	{
		std::cout << "Buffer: \'" << bufferKey << "\' not found." << std::endl;
	}
	
	return foundBuffer;
}

bool GraphicsBufferManager::deleteBuffer( std::string bufferKey )
{
	bool success = false;
	GraphicsBuffer* foundBuffer = nullptr;
	auto iter = mBufferMap.find( bufferKey );

	if ( iter != mBufferMap.end() )
	{
		foundBuffer = iter->second;
		mBufferMap.erase( iter );
		delete foundBuffer;

		success = true;
	}

	return success;
}

void GraphicsBufferManager::clearBuffers()
{
	for ( auto iter = mBufferMap.begin(); iter != mBufferMap.end(); ++iter )
	{
		delete iter->second;
	}

	mBufferMap.clear();
}