#ifndef ITEM_MANAGER_H_
#define ITEM_MANAGER_H_

#include <Trackable.h>
#include <vector>
#include <string>
#include <Vector2D.h>
#include "Item.h"
#include "Powerup.h"

class SettingsFile;
class Level;

class ItemManager : public Trackable
{
public:
	ItemManager();
	~ItemManager();

	void update(float deltaTime);
	void draw();

	void addItemToLevel(EnumItem type, Vector2D position, SettingsFile* levelFile, Level* level);

	void setFoodShowing(bool b) { mIsFoodShowing = b; };
	void setPowerupShowing(bool b) { mIsPowerupShowing = b; };

	inline bool isFoodShowing() const { return mIsFoodShowing; };
	inline bool isPowerupShowing() const { return mIsPowerupShowing; };

	inline Item* getFood() const { return mCurrentFood; };
	inline Powerup* getPowerup() const { return mCurrentPowerup; };

private:
	Item* mCurrentFood = nullptr;
	bool mIsFoodShowing = false;
	Powerup* mCurrentPowerup = nullptr;
	bool mIsPowerupShowing = false;

	void cleanupFood();
	void cleanupPowerup();
};

bool operator==(const Vector2D first, const Vector2D second);

#endif