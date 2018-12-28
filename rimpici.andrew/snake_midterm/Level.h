#ifndef LEVEL_H_
#define LEVEL_H_

#include <Trackable.h>
#include <vector>
#include <Vector2D.h>
#include <set>
#include "ItemManager.h"

class Tile;
class Sprite;
class Snake;
class SpriteSheet;
class SettingsFile;

class Level : public Trackable
{
	friend class LevelManager;
	friend class Powerup;

public:
	void update(float deltaTime);
	void draw();

	void initLevel();
	
	void cleanupLevel();

	Vector2D get2DCoordinate(int index) const;

private:
	SettingsFile* mpLevelData;

	LevelManager* mLevelManager;

	bool mIsInitialized;

	std::vector<Tile*>* mpTiles;
	std::set<EnumItem> mValidPowerups;

	Snake* mpSnake = nullptr;

	ItemManager* mpItemManager = nullptr;

	const int mSPEED_SPAWN;
	const int mSLOW_SPAWN;
	float mSpeedSpawnCounter;
	float mSlowSpawnCounter;

	int mSPEED_PERECENT_SPAWN;
	int mSLOW_PERCENT_SPAWN;

	const int mSTART_SPEED;
	const int mSTART_LENGTH;
	const int mEND_LENGTH;

	const int mSLOW_POWERUP_SPEED;
	const int mSPEED_POWERUP_SPEED;
	
	int mGridWidth;
	int mGridHeight;

	bool mFoodJustEaten = false;
	bool mPowerupJustEaten = false;

	Level(std::string levelData, LevelManager* levelManager);
	~Level();

	void checkForCollision();
	void spawnItemRandomly(EnumItem type);

	void addValidPowerup(EnumItem type);
	void getPowerupToSpawn();

	void getEligibleSpawnPositions(std::vector<Vector2D>& eligiblePositions) const;

	void handleFoodEvent();
	void handlePowerupEvent();
};

#endif