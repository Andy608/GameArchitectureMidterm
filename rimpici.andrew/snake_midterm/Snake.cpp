#include "Snake.h"
#include <string>
#include <SpriteSheet.h>
#include "SnakeNode.h"
#include "SnakeEvents.h"
#include <Animation.h>
#include <EventSystem.h>
#include <GraphicsSystem.h>
#include "EventKeyboardInput.h"
#include "InputSystem.h"
#include "Game.h"

Snake::Snake(const SpriteSheet& pHeadSprites, const SpriteSheet& pBodySprites, const SpriteSheet& pTailSprites, 
	int xPosition, int yPosition, int snakeLength, int movementSpeed, EnumDirection snakeDirection) :
	EventListener(EventSystem::getInstance()),
	mHEAD_SPRITE_SHEET(pHeadSprites),
	mBODY_SPRITE_SHEET(pBodySprites),
	mTAIL_SPRITE_SHEET(pTailSprites),
	mSnakePosition(Vector2D(xPosition, yPosition)),
	mMovementSpeed(movementSpeed),
	mSnakeDirection(snakeDirection)
{
	EventSystem::addListener(EventSnakeDirection::sEVENT_ID, this);
	EventSystem::addListener(EventKeyboardInput::sEVENT_ID, this);

	initSnakeBody();
	snakeLength -= 2;

	if (snakeLength >= MIN_SNAKE_LENGTH)
	{
		growBody(snakeLength, true);
	}

	mIsInLevel = true;
}

Snake::~Snake()
{
	EventSystem::removeListener(EventSnakeDirection::sEVENT_ID, this);
	unsigned int i;
	for (i = 0; i < mSnakeNodeList.size(); ++i)
	{
		delete mSnakeNodeList.at(i);
	}

	mSnakeNodeList.clear();
}

void Snake::growBody(int bodysToAdd, bool pushBackPosition)
{
	int i = 0;
	for (i = 0; i < bodysToAdd; ++i)
	{
		SnakeNode *tailNode = mSnakeNodeList.at(mSnakeNodeList.size() - 1);
		
		//Set position to the tail position
		Vector2D newNodePosition = tailNode->getCurrentPosition();
		
		if (pushBackPosition)
		{
			Vector2D newTailPosition = newNodePosition;
			//Set position to one behind the tail position.
			setPositionFromDirection(tailNode->getCurrentDirection(), newTailPosition, true);

			//Set the tail position to the new position
			tailNode->setPosition(newTailPosition);
		}

		SnakeNode* newNode = new SnakeNode(*this, newNodePosition, initAnimation(mSnakeNodeList.at(mSnakeNodeList.size() - 2), new Animation(mBODY_SPRITE_SHEET.getSprites(), SNAKE_ANIMATION_SPEED, true)), tailNode->getCurrentDirection());


		mSnakeNodeList.insert(mSnakeNodeList.end() - 1, newNode);
		initAnimation(mSnakeNodeList.at(mSnakeNodeList.size() - 2), tailNode->getAnimation());
	}
}

const int Snake::getSnakeLength() const
{
	return mSnakeNodeList.size();
}

void Snake::initSnakeBody()
{
	mSnakeNodeList.push_back(new SnakeNode(*this, mSnakePosition, initAnimation(nullptr, new Animation(mHEAD_SPRITE_SHEET.getSprites(), SNAKE_ANIMATION_SPEED, true)), mSnakeDirection));
	
	SnakeNode* prevNode = mSnakeNodeList.at(mSnakeNodeList.size() - 1);
	Vector2D position = prevNode->getCurrentPosition();
	setPositionFromDirection(prevNode->getCurrentDirection(), position, true);

	mSnakeNodeList.push_back(new SnakeNode(*this, position, new Animation(mTAIL_SPRITE_SHEET.getSprites(), SNAKE_ANIMATION_SPEED, true), prevNode->getCurrentDirection()));
}

Animation* Snake::initAnimation(SnakeNode* prevNode, Animation* nodeAnimation)
{
	if (prevNode != nullptr)
	{
		nodeAnimation->setFrameLengthOffset(prevNode->getAnimation()->getElapsedTime());
		nodeAnimation->setFrameIndex(prevNode->getAnimation()->getCurrentSpriteIndex() + 1);
	}

	return nodeAnimation;
}

void Snake::setPositionFromDirection(EnumDirection direction, Vector2D& position, bool invertOffset)
{
	if (invertOffset)
	{
		switch (direction)
		{
		case NORTH:
			position.setY(position.getY() + 1);
			break;
		case EAST:
			position.setX(position.getX() - 1);
			break;
		case SOUTH:
			position.setY(position.getY() - 1);
			break;
		case WEST:
			position.setX(position.getX() + 1);
			break;
		}
	}
	else
	{
		switch (direction)
		{
		case NORTH:
			position.setY(position.getY() - 1);
			break;
		case EAST:
			position.setX(position.getX() + 1);
			break;
		case SOUTH:
			position.setY(position.getY() + 1);
			break;
		case WEST:
			position.setX(position.getX() - 1);
			break;
		}
	}
}

void Snake::setPosition(int xPosition, int yPosition)
{
	mSnakePosition.setX(static_cast<float>(xPosition));
	mSnakePosition.setY(static_cast<float>(yPosition));
}

void Snake::update(float deltaTime)
{
	unsigned int i;
	for (i = 0; i < mSnakeNodeList.size(); ++i)
	{
		mSnakeNodeList.at(i)->update(deltaTime);
	}

	if (!mMoveSnake)
	{
		return;
	}

	if (mSnakeNodeList.size() > 0)
	{
		mSnakeNodeList.at(0)->setDirection(mSnakeDirection);
	}

	mMovementCounter += deltaTime;

	if (mMovementCounter >= mMovementSpeed)
	{
		moveSnake();
		mMovementCounter = 0;
	}
}

void Snake::draw()
{
	if (!mMoveSnake)
	{
		const Sprite& head = mSnakeNodeList.at(0)->getAnimation()->getCurrentSprite();
		GraphicsSystem::writeText(mSnakePosition.getX() * head.getWidth(), mSnakePosition.getY() * head.getHeight() + 32, *Game::getInstance()->getHelpFont(), *Game::getInstance()->getGUIColor(), "Press the ENTER key to start!");
	}

	unsigned int i;
	for (i = 0; i < mSnakeNodeList.size(); ++i)
	{
		mSnakeNodeList.at(i)->draw();
	}
}

void Snake::moveSnake()
{
	if (mDirectionQueue.size() > 0)
	{
		mSnakeDirection = mDirectionQueue.front();
		mDirectionQueue.pop();
	}

	setPositionFromDirection(mSnakeDirection, mSnakePosition, false);
	
	unsigned int i;
	for (i = mSnakeNodeList.size() - 1; i > 0; --i)
	{
		mSnakeNodeList.at(i)->setPosition(mSnakeNodeList.at(i - 1)->getCurrentPosition());
		mSnakeNodeList.at(i)->setDirection(mSnakeNodeList.at(i - 1)->getCurrentDirection());
	}

	if (mSnakeNodeList.size() > 0)
	{
		mSnakeNodeList.at(0)->setPosition(mSnakePosition);
		mSnakeNodeList.at(0)->setDirection(mSnakeDirection);
	}
}

void Snake::handleEvent(const Event& theEvent)
{
	if (!mIsInLevel)
	{
		return;
	}

	if (!mMoveSnake)
	{
		if (theEvent.mEVENT_ID.compare(EventKeyboardInput::sEVENT_ID) == 0)
		{
			const EventKeyboardInput& keyEvent = static_cast<const EventKeyboardInput&>(theEvent);

			if (keyEvent.getInputCode() == EnumKeyInput::ENTER_KEY)
			{
				mMoveSnake = true;
			}
		}
	}
	else if (theEvent.mEVENT_ID.compare(EventSnakeDirection::sEVENT_ID) == 0)
	{
		const EventSnakeDirection& snakeDirEvent = static_cast<const EventSnakeDirection&>(theEvent);

		if (mMoveSnake && (mDirectionQueue.size() > 0 && mDirectionQueue.back() != snakeDirEvent.getDirection()) ||
			getReverseDirection(mSnakeDirection) != snakeDirEvent.getDirection())
		{
			mDirectionQueue.push(snakeDirEvent.getDirection());
		}
	}
}

bool Snake::collidedWithSelf() const
{
	for (int i = 1; i < mSnakeNodeList.size(); ++i)
	{
		Vector2D bodyPosition = mSnakeNodeList.at(i)->getCurrentPosition();
		if (bodyPosition == mSnakePosition)
		{
			return true;
		}
	}

	return false;
}
