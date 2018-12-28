#include "ItemManager.h"
#include <Animation.h>
#include "Game.h"
#include "SpriteSheet.h"
#include "SettingsFile.h"
#include "Level.h"

ItemManager::ItemManager()
{

}

ItemManager::~ItemManager()
{
	cleanupFood();
	cleanupPowerup();
}

void ItemManager::update(float deltaTime)
{
	if (mCurrentFood != nullptr)
	{
		mCurrentFood->update(deltaTime);
	}

	if (mCurrentPowerup != nullptr)
	{
		mCurrentPowerup->update(deltaTime);
	}
}

void ItemManager::draw()
{
	if (mIsFoodShowing)
	{
		mCurrentFood->draw();
	}

	if (mIsPowerupShowing)
	{
		mCurrentPowerup->draw();
	}
}

void ItemManager::addItemToLevel(EnumItem type, Vector2D position, SettingsFile* levelFile, Level* level)
{
	switch (type)
	{
	case EnumItem::FOOD:
		cleanupFood();
		mCurrentFood = new Item(new Animation(Game::getInstance()->getFoodSprites()->getSprites(), 250, true), position);
		setFoodShowing(true);
		break;
	case EnumItem::SPEED_POWERUP:
		cleanupPowerup();
		mCurrentPowerup = new Powerup(
			EnumItem::SPEED_POWERUP,
			std::stoi(levelFile->getSettingFromKey("speed_powerup_duration")),
			new Animation(Game::getInstance()->getSpeedSprites()->getSprites(), 
				100, 
				true), 
			position,
			level);

		setPowerupShowing(true);
		break;
	case EnumItem::SLOW_POWERUP:
		cleanupPowerup();
		mCurrentPowerup = new Powerup(
			EnumItem::SLOW_POWERUP,
			std::stoi(levelFile->getSettingFromKey("slow_powerup_duration")),
			new Animation(Game::getInstance()->getSlowSprites()->getSprites(),
				500,
				true),
			position,
			level);
		setPowerupShowing(true);
		break;
	}
}

void ItemManager::cleanupFood()
{
	if (mCurrentFood != nullptr)
	{
		delete mCurrentFood;
	}
}

void ItemManager::cleanupPowerup()
{
	if (mCurrentPowerup != nullptr)
	{
		delete mCurrentPowerup;
	}
}

bool operator==(const Vector2D first, const Vector2D second)
{
	return first.getX() == second.getX() && first.getY() == second.getY();
};