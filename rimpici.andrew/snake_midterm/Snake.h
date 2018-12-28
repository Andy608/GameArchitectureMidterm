#ifndef SNAKE_H_
#define SNAKE_H_

#include <EventListener.h>
#include <vector>
#include <queue>
#include <Vector2D.h>

class SpriteSheet;
class SnakeNode;
class Animation;

enum EnumDirection
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

class Snake : public EventListener
{
	friend class Level;
	friend class SnakeNode;
	friend class Powerup;
public:
	Snake(const SpriteSheet& pHeadSprites, const SpriteSheet& pBodySprites, const SpriteSheet& pTailSprites, int xPosition, int yPosition, int snakeLength, int movementSpeed, EnumDirection snakeDirection);
	~Snake();

	const int getSnakeLength() const;
	void growBody(int bodysToAdd, bool pushBackPosition);

	void update(float deltaTime);
	void draw();

	void setPosition(int xPosition, int yPosition);
	inline const Vector2D& getPosition() const { return mSnakePosition; };

	bool collidedWithSelf() const;

	virtual void handleEvent(const Event& theEvent);

private:
	static const int SNAKE_ANIMATION_SPEED = 200;
	static const int MIN_SNAKE_LENGTH = 1;
	std::vector<SnakeNode*> mSnakeNodeList;
	std::queue<EnumDirection> mDirectionQueue;

	bool mMoveSnake = false;
	bool mIsInLevel = false;

	Vector2D mSnakePosition;
	EnumDirection mSnakeDirection;

	int mMovementSpeed;
	float mMovementCounter = 0;

	int mSnakeAnimationIndex = 0;

	const SpriteSheet& mHEAD_SPRITE_SHEET;
	const SpriteSheet& mBODY_SPRITE_SHEET;
	const SpriteSheet& mTAIL_SPRITE_SHEET;

	void initSnakeBody();

	void moveSnake();

	void setPositionFromDirection(EnumDirection direction, Vector2D& position, bool invertOffset);
	inline EnumDirection getDirection() { return mSnakeDirection; };
	EnumDirection getReverseDirection(EnumDirection direction) const { return static_cast<EnumDirection>((static_cast<int>(direction) + 2) % 4); };

	Animation* initAnimation(SnakeNode* prevNode, Animation* nodeAnimation);
};

#endif