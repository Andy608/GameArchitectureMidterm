#include "SnakeNode.h"
#include "Animation.h"
#include <GraphicsSystem.h>
#include "Snake.h"

SnakeNode::SnakeNode(const Snake& parent, Vector2D nodePosition, Animation* pBodyAnimation, EnumDirection direction) :
	mPARENT(parent),
	mpBodyAnimation(pBodyAnimation),
	mCurrentDirection(direction),
	mCurrentPosition(nodePosition)
{

}

SnakeNode::~SnakeNode()
{
	delete mpBodyAnimation;
}

void SnakeNode::update(float deltaTime)
{
	mpBodyAnimation->update(deltaTime);
}

void SnakeNode::draw()
{
	const Sprite& currentSprite = mpBodyAnimation->getCurrentSprite();

	//Rotate nodes depending on direction.

	float rotation =  mCurrentDirection * 90.0f;

	//std::cout << "Alpha: " << std::to_string(alpha) << std::endl;
	//std::cout << "Lerped Pos: " << std::to_string(mLerpedPosition.getX()) << ", " << std::to_string(mLerpedPosition.getY()) << std::endl;

	GraphicsSystem::drawRotated(
		currentSprite.getStartingX(), 
		currentSprite.getStartingY(), 
		currentSprite.getWidth(), currentSprite.getHeight(), 
		(mCurrentPosition.getX() * static_cast<float>(currentSprite.getWidth())) + static_cast<float>(currentSprite.getWidth() / 2.0f),
		(mCurrentPosition.getY() * static_cast<float>(currentSprite.getHeight())) + static_cast<float>(currentSprite.getHeight() / 2.0f),
		mpBodyAnimation->getCurrentSprite().mSPRITE_BUFFER, rotation);
}

void SnakeNode::setPosition(int xPosition, int yPosition)
{
	mCurrentPosition.setX(static_cast<float>(xPosition));
	mCurrentPosition.setY(static_cast<float>(yPosition));
}

void SnakeNode::setPosition(Vector2D position)
{
	mCurrentPosition = position;
}

const Vector2D& SnakeNode::getCurrentPosition() const
{
	return mCurrentPosition;
}