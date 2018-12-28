#ifndef ITEM_H_
#define ITEM_H_

#include <Trackable.h>
#include <Vector2D.h>

class Animation;

enum class EnumItem
{
	FOOD,
	SPEED_POWERUP,
	SLOW_POWERUP
};

class Item : public Trackable
{
public:
	Item(Animation* pAnimation, Vector2D position);
	virtual ~Item();

	inline void setPosition(Vector2D position) { mPosition = position; };
	const Vector2D& getPosition() { return mPosition; };

	virtual void update(float deltaTime);
	void draw();

private:
	Animation* mpItemAnimation;

	Vector2D mPosition;
};

#endif