/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#ifndef GAME_H_
#define GAME_H_

#include <Trackable.h>
#include <EventListener.h>
#include <Color.h>

class Timer;
class GraphicsBufferManager;
class SpriteSheet;
class InputTranslator;
class Tile;
class Sprite;
class LevelManager;
class SettingsFile;
class TileFactory;
class Font;

enum class EnumScene
{
	TITLE_SCENE,
	LEVEL_SCENE,
	WIN_SCENE,
	LOSE_SCENE
};

class Game : public EventListener
{
public:
	static Game* getInstance();
	static bool initInstance();
	static void cleanupInstance();

	//Disable any form of copying for a Game object.
	Game( const Game& copy ) = delete;
	void operator=( const Game& copy ) = delete;

	bool init( const int& displayWidth, const int& displayHeight );
	void cleanup();

	void loop();

	virtual void handleEvent( const Event& theEvent );

	inline GraphicsBufferManager* getBufferManager() const { return mpBufferManager; };
	inline TileFactory* getTileFactory() const { return mpTileFactory; };

	inline SpriteSheet* getHeadSprites() const { return mpHeadSprites; };
	inline SpriteSheet* getBodySprites() const { return mpBodySprites; };
	inline SpriteSheet* getTailSprites() const { return mpTailSprites; };

	inline SpriteSheet* getFoodSprites() const { return mpFoodSprites; };
	inline SpriteSheet* getSpeedSprites() const { return mpSpeedSprites; };
	inline SpriteSheet* getSlowSprites() const { return mpSlowSprites; };

	inline Font* getGUIFont() const { return mpGUIFont; };
	inline Font* getHelpFont() const { return mpHelpFont; };
	inline Color* getGUIColor() const { return mpTextColor; };

private:
	static Game* smpInstance;
	static const int ANIMATION_SPEED_OFFSET;
	static const float mFPS;
	static const float mUPDATE_TIME;//Timer is in milliseconds
	static const float mLAG_CAP;//Timer is in milliseconds


	//Asset variables
	const std::string mDRAW_TRACKER_NAME = "draw";
	std::string mFontSrc;
	int mTitleFontSize;
	int mGUIFontSize;
	int mHelpFontSize;

	int mFrames;

	bool mIsInitialized = false;
	bool mIsLoopRunning = false;
	bool mShouldShutdown = false;
	bool mIsAnimating = true;

	Timer* mpTimer = nullptr;

	GraphicsBufferManager* mpBufferManager = nullptr;

	SpriteSheet* mpHeadSprites = nullptr;
	SpriteSheet* mpBodySprites = nullptr;
	SpriteSheet* mpTailSprites = nullptr;

	SpriteSheet* mpFoodSprites = nullptr;
	SpriteSheet* mpSpeedSprites = nullptr;
	SpriteSheet* mpSlowSprites = nullptr;

	SettingsFile* mpMainSettingsFile = nullptr;

	LevelManager* mpLevelManager = nullptr;

	TileFactory* mpTileFactory = nullptr;

	InputTranslator* mpInputTranslator = nullptr;

	EnumScene mCurrentScene = EnumScene::TITLE_SCENE;

	Font* mpTitleFont = nullptr;
	Font* mpGUIFont = nullptr;
	Font* mpHelpFont = nullptr;
	Color* mpTextColor = nullptr;

	int mScore;

	Game();
	~Game();

	void update( float deltaTime );
	void render();

	void updateTitleScene(float deltaTime);
	void updateLevelScene(float deltaTime);
	void updateWinScene(float deltaTime);
	void updateLoseScene(float deltaTime);

	void renderTitleScene();
	void renderLevelScene();
	void renderWinScene();
	void renderLoseScene();
};

#endif