/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Game.h"
#include <Timer.h>
#include <System.h>
#include <EventSystem.h>
#include <EventKeyboardInput.h>
#include <EventWindowClosed.h>
#include "GraphicsBufferManager.h"
#include <SpriteSheet.h>
#include "InputTranslator.h"
#include "Animation.h"
#include "Tile.h"
#include "SettingsFile.h"
#include "TileFactory.h"
#include "LevelManager.h"
#include "SnakeEvents.h"
#include "EventGoToNextLevel.h"
#include <Font.h>
#include <assert.h>
#include <PerformanceTracker.h>
#include "Level.h"
#include "EventAddScore.h"

Game* Game::smpInstance = nullptr;

const int Game::ANIMATION_SPEED_OFFSET = 10;
const float Game::mFPS = 60.0f;
const float Game::mUPDATE_TIME = (1.0f / mFPS) * 1000.0f;//Timer is in milliseconds
const float Game::mLAG_CAP = 0.15f * 1000.0f;//Timer is in milliseconds

Game* Game::getInstance()
{
	assert( smpInstance );
	return smpInstance;
}

bool Game::initInstance()
{
	if ( !smpInstance )
	{
		std::cout << "Game instance is null, creating new instance." << std::endl;
		smpInstance = new Game();
	}

	return smpInstance;
}

void Game::cleanupInstance()
{
	delete smpInstance;
	smpInstance = nullptr;
}

Game::Game() : EventListener( EventSystem::getInstance() )
{
	EventSystem::addListener( EventKeyboardInput::sEVENT_ID, this );
	EventSystem::addListener( EventWindowClosed::sEVENT_ID, this );
	EventSystem::addListener( EventSnakeHitWall::sEVENT_ID, this );
	EventSystem::addListener( EventSnakeHitSelf::sEVENT_ID, this );
	EventSystem::addListener( EventGoToNextLevel::sEVENT_ID, this );
	EventSystem::addListener( EventAddScore::sEVENT_ID, this );
}

Game::~Game()
{
	cleanup();
}

bool Game::init( const int& displayWidth, const int& displayHeight )
{
	if ( !mIsInitialized )
	{
		mpTimer = new Timer();

		static const std::string ASSETS_PATH = "..\\..\\shared\\assets\\";
		static const std::string WOOD_FILENAME = "Woods.png";

		mIsInitialized = true;

		if ( System::initInstance( displayWidth, displayHeight ) )
		{
			mpBufferManager = new GraphicsBufferManager( GraphicsSystem::getBackBuffer() );
			
			mpMainSettingsFile = new SettingsFile("assets/data_files/game_data.txt");
			mpBufferManager->addBuffer( "wood_buffer", new GraphicsBuffer(mpMainSettingsFile->getSettingFromKey("background_sprite")));

			//The file will have the snake filenames in it.
			mpBufferManager->addBuffer("snake_head_spritesheet", new GraphicsBuffer(mpMainSettingsFile->getSettingFromKey("head_sprites")));
			mpBufferManager->addBuffer("snake_body_spritesheet", new GraphicsBuffer(mpMainSettingsFile->getSettingFromKey("body_sprites")));
			mpBufferManager->addBuffer("snake_tail_spritesheet", new GraphicsBuffer(mpMainSettingsFile->getSettingFromKey("tail_sprites")));

			mpBufferManager->addBuffer("food_spritesheet", new GraphicsBuffer(mpMainSettingsFile->getSettingFromKey("food_sprites")));
			mpBufferManager->addBuffer("speed_spritesheet", new GraphicsBuffer(mpMainSettingsFile->getSettingFromKey("speed_sprites")));
			mpBufferManager->addBuffer("slow_spritesheet", new GraphicsBuffer(mpMainSettingsFile->getSettingFromKey("slow_sprites")));
			
			mFontSrc = mpMainSettingsFile->getSettingFromKey("font_src");
			mTitleFontSize = std::stoi(mpMainSettingsFile->getSettingFromKey("title_font_size"));
			mGUIFontSize = std::stoi(mpMainSettingsFile->getSettingFromKey("gui_font_size"));
			mHelpFontSize = std::stoi(mpMainSettingsFile->getSettingFromKey("help_font_size"));

			mpTitleFont = new Font(mFontSrc, mTitleFontSize);
			mpGUIFont = new Font(mFontSrc, mGUIFontSize);
			mpHelpFont = new Font(mFontSrc, mHelpFontSize);

			mpTextColor = new Color(255, 255, 255);

			std::string tileDataFile = mpMainSettingsFile->getSettingFromKey("tile_data");
			mpTileFactory = new TileFactory(tileDataFile);
			
			const int SPRITE_SIZE = std::stoi(mpMainSettingsFile->getSettingFromKey("sprite_size"));

			mpHeadSprites = new SpriteSheet(*mpBufferManager->getBuffer("snake_head_spritesheet"), 1, 7, SPRITE_SIZE, SPRITE_SIZE);
			mpBodySprites = new SpriteSheet(*mpBufferManager->getBuffer("snake_body_spritesheet"), 1, 7, SPRITE_SIZE, SPRITE_SIZE);
			mpTailSprites = new SpriteSheet(*mpBufferManager->getBuffer("snake_tail_spritesheet"), 1, 7, SPRITE_SIZE, SPRITE_SIZE);

			mpFoodSprites = new SpriteSheet(*mpBufferManager->getBuffer("food_spritesheet"), 1, 2, SPRITE_SIZE, SPRITE_SIZE);
			mpSpeedSprites = new SpriteSheet(*mpBufferManager->getBuffer("speed_spritesheet"), 1, 2, SPRITE_SIZE, SPRITE_SIZE);
			mpSlowSprites = new SpriteSheet(*mpBufferManager->getBuffer("slow_spritesheet"), 1, 2, SPRITE_SIZE, SPRITE_SIZE);

			mpInputTranslator = new InputTranslator();

			mpLevelManager = new LevelManager();
			mpLevelManager->addLevel(mpMainSettingsFile->getSettingFromKey("level1"));
			mpLevelManager->addLevel(mpMainSettingsFile->getSettingFromKey("level2"));
			mpLevelManager->addLevel(mpMainSettingsFile->getSettingFromKey("level3"));

			if ( !mpInputTranslator->init() )
			{
				std::cout << "Error initializing Input Translator." << std::endl;
				cleanup();
			}
		}
		else
		{
			std::cout << "Error initializing System." << std::endl;
			cleanup();
		}
	}

	return mIsInitialized;
}

void Game::cleanup()
{
	if ( mIsInitialized )
	{
		delete mpMainSettingsFile;

		delete mpTextColor;

		delete mpTitleFont;
		delete mpHelpFont;
		delete mpGUIFont;

		delete mpTileFactory;

		delete mpSlowSprites;
		delete mpSpeedSprites;
		delete mpFoodSprites;

		delete mpHeadSprites;
		delete mpBodySprites;
		delete mpTailSprites;

		delete mpLevelManager;

		if ( mpBufferManager )
		{
			delete mpBufferManager;
			mpBufferManager = nullptr;
		}

		if ( mpInputTranslator )
		{
			delete mpInputTranslator;
			mpInputTranslator = nullptr;
		}

		if ( mpTimer )
		{
			delete mpTimer;
			mpTimer = nullptr;
		}

		System::cleanupInstance();

		mIsInitialized = false;
		mIsLoopRunning = false;
	}
}

void Game::loop()
{
	if ( !mIsInitialized )
	{
		std::cout << "The game is not initialized yet." << std::endl;
	}
	else if ( mIsLoopRunning )
	{
		std::cout << "The game loop is already running." << std::endl;
	}
	else
	{
		//Start the loop
		mIsLoopRunning = true;
		
		mpTimer->start();

		PerformanceTracker* pPerformanceTracker = new PerformanceTracker;
		pPerformanceTracker->startTracking(mDRAW_TRACKER_NAME);

		while (!mShouldShutdown)
		{
			pPerformanceTracker->clearTracker(mDRAW_TRACKER_NAME);
			pPerformanceTracker->startTracking(mDRAW_TRACKER_NAME);
			mpTimer->start();
			update(mUPDATE_TIME);
			render();

			mpTimer->sleepUntilElapsed(mUPDATE_TIME);
			pPerformanceTracker->stopTracking(mDRAW_TRACKER_NAME);
			mFrames = static_cast<int>(round(1000.0f / pPerformanceTracker->getElapsedTime(mDRAW_TRACKER_NAME)));
			std::cout << "Elapsed Time: " << pPerformanceTracker->getElapsedTime(mDRAW_TRACKER_NAME) << " milliseconds" << std::endl;
		}

		mIsLoopRunning = false;

		delete pPerformanceTracker;
	}
}

void Game::update( float deltaTime )
{
	System::getInstance()->getInputSystem()->update( deltaTime );

	//mpUnitManager->update( deltaTime );

	switch (mCurrentScene)
	{
	case EnumScene::TITLE_SCENE:
		updateTitleScene(deltaTime);
		break;
	case EnumScene::LEVEL_SCENE:
		updateLevelScene(deltaTime);
		break;
	case EnumScene::WIN_SCENE:
		updateWinScene(deltaTime);
		break;
	case EnumScene::LOSE_SCENE:
		updateLoseScene(deltaTime);
		break;
	}

}

void Game::render()
{
	GraphicsSystem::drawScaledToFit( 0, 0, *mpBufferManager->getBuffer( "wood_buffer" ), 
		static_cast<float>( GraphicsSystem::getDisplayWidth() ), static_cast<float>( GraphicsSystem::getDisplayHeight() ) );
	
	switch (mCurrentScene)
	{
	case EnumScene::TITLE_SCENE:
		renderTitleScene();
		break;
	case EnumScene::LEVEL_SCENE:
		renderLevelScene();
		break;
	case EnumScene::WIN_SCENE:
		renderWinScene();
		break;
	case EnumScene::LOSE_SCENE:
		renderLoseScene();
		break;
	}

	//mpUnitManager->draw();

	GraphicsSystem::flip();
}

void Game::handleEvent( const Event& theEvent )
{
	if ( theEvent.mEVENT_ID.compare( EventWindowClosed::sEVENT_ID ) == 0 )
	{
		mShouldShutdown = true;
	}
	else if (theEvent.mEVENT_ID.compare(EventKeyboardInput::sEVENT_ID) == 0)
	{
		const EventKeyboardInput& keyEvent = static_cast<const EventKeyboardInput&>(theEvent);

		switch (mCurrentScene)
		{
		case EnumScene::TITLE_SCENE:
			//Click any button to go from the menu scene to the level scene
			if (keyEvent.getInputCode() == EnumKeyInput::SPACE_KEY)
			{
				mCurrentScene = EnumScene::LEVEL_SCENE;

				if (mpLevelManager != nullptr)
				{
					mpLevelManager->reset();
					mpLevelManager->setCurrentLevel(0);
				}
			}
			break;
		case EnumScene::WIN_SCENE: 
		case EnumScene::LOSE_SCENE:
			//Click any button to go from the menu scene to the level scene
			if (keyEvent.getInputCode() == EnumKeyInput::SPACE_KEY)
			{
				//mScore = 0;
				//mCurrentScene = EnumScene::TITLE_SCENE;
				mShouldShutdown = true;
			}
			break;
		}
	}
	else if (theEvent.mEVENT_ID.compare(EventSnakeHitSelf::sEVENT_ID) == 0 ||
		theEvent.mEVENT_ID.compare(EventSnakeHitWall::sEVENT_ID) == 0)
	{
		switch (mCurrentScene)
		{
		case EnumScene::LEVEL_SCENE:
			mCurrentScene = EnumScene::LOSE_SCENE;
			break;
		}
	}
	else if (theEvent.mEVENT_ID.compare(EventGoToNextLevel::sEVENT_ID) == 0)
	{
		//If there are no levels left, go to the end scene
		if (!mpLevelManager->goToNextLevel())
		{
			//Go to end screen.
			mCurrentScene = EnumScene::WIN_SCENE;
		}
	}
	else if (theEvent.mEVENT_ID.compare(EventAddScore::sEVENT_ID) == 0)
	{
		const EventAddScore& addScoreEvent = static_cast<const EventAddScore&>(theEvent);
		mScore += addScoreEvent.getScoreToAdd();
	}
}

void Game::updateTitleScene(float deltaTime)
{
	
}

void Game::updateLevelScene(float deltaTime)
{
	mpLevelManager->update(deltaTime);
}

void Game::updateWinScene(float deltaTime)
{
	
}

void Game::updateLoseScene(float deltaTime)
{

}

void Game::renderTitleScene()
{
	GraphicsSystem::writeText(500, 100, *mpTitleFont, *mpTextColor, "SNAKE!");
	GraphicsSystem::writeText(500, 500, *mpTitleFont, *mpTextColor, "Press Space to Continue");
	GraphicsSystem::writeText(100, 0, *mpGUIFont, *mpTextColor, "FPS: " + std::to_string(mFrames));
}

void Game::renderLevelScene()
{
	mpLevelManager->draw();
	GraphicsSystem::writeText(100, 30, *mpGUIFont, *mpTextColor, "Level: " + std::to_string(mpLevelManager->getCurrentLevelIndex() + 1));
	GraphicsSystem::writeText(100, 60, *mpGUIFont, *mpTextColor, "Score: " + std::to_string(mScore));
	GraphicsSystem::writeText(100, 0, *mpGUIFont, *mpTextColor, "FPS: " + std::to_string(mFrames));
}

void Game::renderWinScene()
{
	GraphicsSystem::writeText(500, 100, *mpTitleFont, *mpTextColor, "You Win! :D");
	GraphicsSystem::writeText(500, 500, *mpTitleFont, *mpTextColor, "Press Space to Continue");
	GraphicsSystem::writeText(500, 300, *mpGUIFont, *mpTextColor, "You Scored: " + std::to_string(mScore));
	GraphicsSystem::writeText(100, 0, *mpGUIFont, *mpTextColor, "FPS: " + std::to_string(mFrames));
}

void Game::renderLoseScene()
{
	GraphicsSystem::writeText(500, 100, *mpTitleFont, *mpTextColor, "You Lose :(");
	GraphicsSystem::writeText(500, 500, *mpTitleFont, *mpTextColor, "Press Space to Continue");
	GraphicsSystem::writeText(500, 300, *mpGUIFont, *mpTextColor, "You Scored: " + std::to_string(mScore));
	GraphicsSystem::writeText(100, 0, *mpGUIFont, *mpTextColor, "FPS: " + std::to_string(mFrames));
}