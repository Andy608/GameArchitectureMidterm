#ifndef LEVEL_MANAGER_H_
#define LEVEL_MANAGER_H_

#include <Trackable.h>
#include <vector>

class Level;

class LevelManager : public Trackable
{
public:
	LevelManager();
	~LevelManager();

	inline const Level* getCurrentLevel() const { return mCurrentLevel; };
	inline const int getCurrentLevelIndex() const { return mLevelIndex; };

	void addLevel(std::string levelDataFileSrc);
	void setCurrentLevel(int index);

	void reset();

	bool goToNextLevel();

	void update(float deltaTime);
	void draw();

private:
	int mLevelIndex;
	Level* mCurrentLevel;
	std::vector<Level*> mLevels;
};

#endif