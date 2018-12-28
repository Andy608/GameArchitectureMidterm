#ifndef SNAKE_NODE_H_
#define SNAKE_NODE_H_

#include <Trackable.h>
#include <Vector2D.h>
#include "Snake.h"

class Animation;

class SnakeNode : public Trackable
{
public:
	SnakeNode(const Snake& parent, Vector2D nodePosition, Animation* pBodyAnimation, EnumDirection direction);
	~SnakeNode();

	void update(float deltaTime);
	void draw();

	void setPosition(int xPosition, int yPosition);
	void setPosition(Vector2D position);
	const Vector2D& getCurrentPosition() const;

	inline void setDirection(EnumDirection direction) { mCurrentDirection = direction; };
	inline EnumDirection getCurrentDirection() { return mCurrentDirection; };

	inline Animation* getAnimation() const { return mpBodyAnimation; };

private:
	const Snake& mPARENT;

	Animation* mpBodyAnimation;

	EnumDirection mCurrentDirection;
	Vector2D mCurrentPosition;
};

#endif