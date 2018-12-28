#include "Tile.h"
#include <Sprite.h>
#include <GraphicsSystem.h>

Tile::Tile( Sprite *pSprite, int xPosition, int yPosition, bool isWall ) :
	mpDefaultSprite( pSprite ),
	mIsWall( isWall ),
	mPosition( Vector2D( xPosition, yPosition ) )
{

}

Tile::~Tile()
{

}

void Tile::update( float deltaTime )
{

}

void Tile::draw()
{
	GraphicsSystem::draw( mPosition.getX() * mpDefaultSprite->getWidth(), mPosition.getY() * mpDefaultSprite->getHeight(), *mpDefaultSprite );
}

void Tile::setPosition( int xPosition, int yPosition )
{
	mPosition.setX( xPosition );
	mPosition.setY( yPosition );
}