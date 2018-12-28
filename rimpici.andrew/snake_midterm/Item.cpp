#include "Item.h"
#include <Animation.h>
#include <GraphicsSystem.h>

Item::Item(Animation* pAnimation, Vector2D position) :
	mpItemAnimation(pAnimation),
	mPosition(position)
{

}

Item::~Item()
{
	delete mpItemAnimation;
}

void Item::update(float deltaTime)
{
	mpItemAnimation->update(deltaTime);
}

void Item::draw()
{
	const Sprite& currentSprite = mpItemAnimation->getCurrentSprite();
	GraphicsSystem::draw(mPosition.getX() * currentSprite.getWidth(), mPosition.getY() * currentSprite.getHeight(), currentSprite);
}