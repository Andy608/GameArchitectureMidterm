#ifndef POWERUP_H_
#define POWERUP_H_

#include "Item.h"

class Level;
class Snake;

class Powerup : public Item
{
public:
	Powerup(EnumItem type, int duration, Animation* pAnimation, Vector2D position, Level* level);
	virtual ~Powerup();

	virtual void update(float update);

	void setActive(bool b) { mIsActive = b; };
	inline bool isActive() const { return mIsActive; };
	inline EnumItem getType() const { return mType; };

private:
	const int mDURATION;
	int mDurationCounter;

	Level* mLevel;
	EnumItem mType;
	bool mIsActive;
};

#endif