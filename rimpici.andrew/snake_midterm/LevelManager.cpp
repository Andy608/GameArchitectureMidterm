#include "LevelManager.h"
#include "Level.h"
#include <assert.h>

LevelManager::LevelManager()
{

}

LevelManager::~LevelManager()
{
	unsigned int i;
	for (i = 0; i < mLevels.size(); ++i)
	{
		delete mLevels.at(i);
	}

	mLevels.clear();
}

void LevelManager::addLevel(std::string levelDataFileSrc)
{
	Level* newLevel = new Level(levelDataFileSrc, this);
	mLevels.push_back(newLevel);
}

void LevelManager::setCurrentLevel(int index)
{
	assert(!mLevels.empty());

	if (index < 0)
	{
		index = 0;
	}
	else if (index >= mLevels.size())
	{
		index = mLevels.size() - 1;
	}

	mLevelIndex = index;
	mCurrentLevel = mLevels.at(mLevelIndex);
	mCurrentLevel->initLevel();
}

void LevelManager::update(float deltaTime)
{
	if (mCurrentLevel != nullptr && mCurrentLevel->mIsInitialized)
	{
		mCurrentLevel->update(deltaTime);
	}
}

void LevelManager::draw()
{
	if (mCurrentLevel != nullptr && mCurrentLevel->mIsInitialized)
	{
		mCurrentLevel->draw();
	}
}

void LevelManager::reset()
{
	for (unsigned int i = 0; i < mLevels.size(); ++i)
	{
		mLevels.at(i)->cleanupLevel();
	}
}

bool LevelManager::goToNextLevel()
{
	mCurrentLevel->cleanupLevel();

	bool isThereANextLevel = true;
	int levelIndex = mLevelIndex + 1;

	if (levelIndex >= mLevels.size())
	{
		isThereANextLevel = false;
	}
	else
	{
		setCurrentLevel(levelIndex);
	}

	return isThereANextLevel;
}