#include "Level.h"
#include "Tile.h"
#include <Sprite.h>
#include "Snake.h"
#include "SnakeNode.h"
#include <SpriteSheet.h>
#include "Game.h"
#include "SettingsFile.h"
#include "GraphicsBufferManager.h"
#include "TileFactory.h"
#include <stdlib.h>
#include <EventSystem.h>
#include <time.h>
#include "SnakeEvents.h"
#include "EventGoToNextLevel.h"
#include "EventAddScore.h"
#include "EventPowerupEnd.h"
#include "LevelManager.h"

Level::Level(std::string levelData, LevelManager* levelManager) :
	mpLevelData(new SettingsFile(levelData)),
	mpTiles(new std::vector<Tile*>()),
	mSTART_SPEED(std::stoi(mpLevelData->getSettingFromKey("start_speed"))),
	mSTART_LENGTH(std::stoi(mpLevelData->getSettingFromKey("start_length"))),
	mEND_LENGTH(std::stoi(mpLevelData->getSettingFromKey("end_length"))),
	mSPEED_SPAWN(std::stoi(mpLevelData->getSettingFromKey("speed_powerup_freq"))),
	mSLOW_SPAWN(std::stoi(mpLevelData->getSettingFromKey("slow_powerup_freq"))),
	mSPEED_PERECENT_SPAWN(std::stoi(mpLevelData->getSettingFromKey("speed_powerup_%"))),
	mSLOW_PERCENT_SPAWN(std::stoi(mpLevelData->getSettingFromKey("slow_powerup_%"))),
	mSLOW_POWERUP_SPEED(std::stoi(mpLevelData->getSettingFromKey("slow_powerup_speed"))),
	mSPEED_POWERUP_SPEED(std::stoi(mpLevelData->getSettingFromKey("speed_powerup_speed"))),
	mLevelManager(levelManager)
{
	srand(static_cast<unsigned int>(time(NULL)));
}

Level::~Level()
{
	cleanupLevel();

	delete mpTiles;
	mpTiles = nullptr;

	delete mpLevelData;
	mpLevelData = nullptr;
}

void Level::initLevel()
{
	if ( !mIsInitialized )
	{
		GraphicsBuffer levelMap = GraphicsBuffer(mpLevelData->getSettingFromKey("map"));

		mGridWidth = levelMap.getWidth();
		mGridHeight = levelMap.getHeight();

		unsigned int tileCount = mGridWidth * mGridHeight;

		unsigned int i;
		for (i = 0; i < tileCount; ++i)
		{
			Vector2D position = get2DCoordinate(i);
			mpTiles->push_back(Game::getInstance()->getTileFactory()->createNewTileFromColor(
				levelMap.getPixelColor(static_cast<int>(position.getX()), static_cast<int>(position.getY())), 
				static_cast<int>(position.getX()), static_cast<int>(position.getY())));
		}

		mpItemManager = new ItemManager();

		mpSnake = new Snake(*Game::getInstance()->getHeadSprites(), *Game::getInstance()->getBodySprites(), *Game::getInstance()->getTailSprites(), 
			std::stoi(mpLevelData->getSettingFromKey("start_x")), 
			std::stoi(mpLevelData->getSettingFromKey("start_y")),
			mSTART_LENGTH,
			mSTART_SPEED,
			(EnumDirection)std::stoi(mpLevelData->getSettingFromKey("start_direction")));

		spawnItemRandomly(EnumItem::FOOD);

		mIsInitialized = true;
	}
}

void Level::cleanupLevel()
{
	if ( mIsInitialized )
	{
		unsigned int i;
		for (i = 0; i < mpTiles->size(); ++i)
		{
			delete mpTiles->at(i);
		}

		mpTiles->clear();

		delete mpItemManager;
		mpItemManager = nullptr;

		delete mpSnake;
		mpSnake = nullptr;

		mFoodJustEaten = false;
		mPowerupJustEaten = false;

		mIsInitialized = false;
	}
}

Vector2D Level::get2DCoordinate(int index) const
{
	return Vector2D(index % mGridWidth, index / mGridWidth);
}

void Level::update(float deltaTime)
{
	unsigned int i;
	for ( i = 0; i < mpTiles->size(); ++i)
	{
		mpTiles->at(i)->update(deltaTime);
	}

	mpItemManager->update(deltaTime);

	if (mpItemManager->getPowerup() != nullptr && !mpItemManager->getPowerup()->isActive())
	{
		if (mValidPowerups.find(mpItemManager->getPowerup()->getType()) != mValidPowerups.end())
		{
			mValidPowerups.erase(mValidPowerups.find(mpItemManager->getPowerup()->getType()));
		}
	}

	mSpeedSpawnCounter += deltaTime;
	if (mSpeedSpawnCounter >= mSPEED_SPAWN)
	{
		mSpeedSpawnCounter = 0;
		//CAN SPAWN
		addValidPowerup(EnumItem::SPEED_POWERUP);
	}

	mSlowSpawnCounter += deltaTime;
	if (mSlowSpawnCounter >= mSLOW_SPAWN)
	{
		mSlowSpawnCounter = 0;
		//CAN SPAWN
		addValidPowerup(EnumItem::SLOW_POWERUP);
	}

	mpSnake->update(deltaTime);

	checkForCollision();

	if (mFoodJustEaten)
	{
		mFoodJustEaten = false;
		handleFoodEvent();
	}

	if (mPowerupJustEaten)
	{
		mPowerupJustEaten = false;
		handlePowerupEvent();
	}
}

void Level::draw()
{
	unsigned int i;
	for (i = 0; i < mpTiles->size(); ++i)
	{
		mpTiles->at(i)->draw();
	}

	mpItemManager->draw();

	mpSnake->draw();
}

void Level::checkForCollision()
{
	const Vector2D snakePosition = mpSnake->getPosition();
	
	unsigned int i;
	for (i = 0; i < mpTiles->size(); ++i)
	{
		Tile* t = mpTiles->at(i);

		if (snakePosition == t->getPosition() && t->isWall())
		{
			//SNAKE HIT THE WALL
			EventSystem::fireEvent(EventSnakeHitWall());
			return;
		}
		else if (!mFoodJustEaten && mpItemManager->isFoodShowing() && snakePosition == mpItemManager->getFood()->getPosition())
		{
			//SEND SNAKE HIT FOOD
			mFoodJustEaten = true;
			return;
		}
		else if (!mPowerupJustEaten && mpItemManager->isPowerupShowing() && snakePosition == mpItemManager->getPowerup()->getPosition())
		{
			//SNAKE HIT POWERUP
			mPowerupJustEaten = true;
			return;
		}
	}

	if (mpSnake->collidedWithSelf())
	{
		//SNAKE HIT SELF EVENT
		EventSystem::fireEvent(EventSnakeHitSelf());
	}
}

void Level::spawnItemRandomly(EnumItem type)
{
	std::vector<Vector2D> eligiblePositions;

	if (type == EnumItem::FOOD)
	{
		if (!mpItemManager->isFoodShowing())
		{
			//Get list of possible tile places.
			getEligibleSpawnPositions(eligiblePositions);

			if (eligiblePositions.size() > 0)
			{
				mpItemManager->addItemToLevel(EnumItem::FOOD, eligiblePositions.at(rand() % eligiblePositions.size()), mpLevelData, this);
			}
		}
	}
	else if (type == EnumItem::SPEED_POWERUP)
	{
		if (!mpItemManager->isPowerupShowing())
		{
			//Get list of possible tile places.
			getEligibleSpawnPositions(eligiblePositions);

			if (eligiblePositions.size() > 0)
			{
				mpItemManager->addItemToLevel(EnumItem::SPEED_POWERUP, eligiblePositions.at(rand() % eligiblePositions.size()), mpLevelData, this);
			}
		}
	}
	else if (type == EnumItem::SLOW_POWERUP)
	{
		if (!mpItemManager->isPowerupShowing())
		{
			//Get list of possible tile places.
			getEligibleSpawnPositions(eligiblePositions);

			if (eligiblePositions.size() > 0)
			{
				mpItemManager->addItemToLevel(EnumItem::SLOW_POWERUP, eligiblePositions.at(rand() % eligiblePositions.size()), mpLevelData, this);
			}
		}
	}
}

void Level::addValidPowerup(EnumItem type)
{
	if (mValidPowerups.find(type) == mValidPowerups.end())
	{
		mValidPowerups.insert(type);

		//Try to place one.
		getPowerupToSpawn();
	}
}

void Level::getPowerupToSpawn()
{
	int totalPercent = mSPEED_PERECENT_SPAWN + mSLOW_PERCENT_SPAWN;
	int percentage = rand() % totalPercent;

	if (percentage < mSPEED_PERECENT_SPAWN)
	{
		//Spawn speed thing.
		spawnItemRandomly(EnumItem::SPEED_POWERUP);
	}
	else if (percentage < (mSPEED_PERECENT_SPAWN + mSLOW_PERCENT_SPAWN))
	{
		//Spawn slow thing.
		spawnItemRandomly(EnumItem::SLOW_POWERUP);
	}
}

void Level::getEligibleSpawnPositions(std::vector<Vector2D>& eligiblePositions) const
{
	unsigned int i;
	for (i = 0; i < mpTiles->size(); ++i)
	{
		Tile* t = mpTiles->at(i);
		bool validPosition = true;

		if (t->isWall() || 
			((mpItemManager->getFood() != nullptr && mpItemManager->getPowerup() != nullptr) && 
				mpItemManager->getFood()->getPosition() == mpItemManager->getPowerup()->getPosition()))
		{
			validPosition = false;
		}
		else
		{
			unsigned int j;
			for (j = 0; j < mpSnake->mSnakeNodeList.size(); ++j)
			{
				if (t->getPosition() == mpSnake->mSnakeNodeList.at(j)->getCurrentPosition())
				{
					validPosition = false;
					break;
				}
			}
		}

		if (validPosition)
		{
			eligiblePositions.push_back(t->getPosition());
		}
	}
}

void Level::handleFoodEvent()
{
	mpItemManager->setFoodShowing(false);
	spawnItemRandomly(EnumItem::FOOD);
	mpSnake->growBody(std::stoi(mpLevelData->getSettingFromKey("growth_amount")), false);
	EventSystem::fireEvent(EventAddScore(std::stoi(mpLevelData->getSettingFromKey("food_points"))));

	if (mpSnake->getSnakeLength() == mEND_LENGTH)
	{
		EventSystem::fireEvent(EventGoToNextLevel());
	}
}

void Level::handlePowerupEvent()
{
	mpItemManager->setPowerupShowing(false);
	mpItemManager->getPowerup()->setActive(true);
	EventSystem::fireEvent(EventAddScore(std::stoi(mpLevelData->getSettingFromKey("powerup_points"))));

	if (mpItemManager->getPowerup()->isActive() && mpItemManager->getPowerup()->getType() == EnumItem::SLOW_POWERUP)
	{
		mpSnake->mMovementSpeed = mSLOW_POWERUP_SPEED;
	}
	
	if (mpItemManager->getPowerup()->isActive() && mpItemManager->getPowerup()->getType() == EnumItem::SPEED_POWERUP)
	{
		mpSnake->mMovementSpeed = mSPEED_POWERUP_SPEED;
	}
}