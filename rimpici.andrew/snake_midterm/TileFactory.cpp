#include "Tile.h"
#include "SettingsFile.h"
#include "TileFactory.h"
#include "Sprite.h"
#include "Game.h"
#include "GraphicsBufferManager.h"
#include <string>

TileFactory::TileFactory(std::string tileaDataSrc) :
	mpTileSettings(new SettingsFile(tileaDataSrc))
{
	Game::getInstance()->getBufferManager()->addBuffer(WALL_TILE_IMAGE, new GraphicsBuffer(mpTileSettings->getSettingFromKey(WALL_TILE_IMAGE)));
	Game::getInstance()->getBufferManager()->addBuffer(FLOOR_TILE_IMAGE, new GraphicsBuffer(mpTileSettings->getSettingFromKey(FLOOR_TILE_IMAGE)));

	GraphicsBuffer* wallTile = Game::getInstance()->getBufferManager()->getBuffer(WALL_TILE_IMAGE);
	mWallTileSprite = new Sprite(*wallTile, 0, 0, wallTile->getWidth(), wallTile->getHeight());

	GraphicsBuffer* floorTile = Game::getInstance()->getBufferManager()->getBuffer(FLOOR_TILE_IMAGE);
	mFloorTileSprite = new Sprite(*floorTile, 0, 0, floorTile->getWidth(), floorTile->getHeight());
}

TileFactory::~TileFactory()
{
	delete mWallTileSprite;
	delete mFloorTileSprite;
	delete mpTileSettings;
}

Tile* TileFactory::createNewTileFromColor(Color color, int x, int y) const
{
	Tile* tile = nullptr;

	std::string colorString = std::to_string(color.red) + "," + std::to_string(color.green) 
							+ "," + std::to_string(color.blue) + "," + std::to_string(color.alpha);

	std::string tileType = mpTileSettings->getKeyFromSetting(colorString);

	if (tileType.compare(std::string("floor_tile")) == 0)
	{
		tile = new Tile(mFloorTileSprite, x, y, false);
	}
	else
	{
		tile = new Tile(mWallTileSprite, x, y, true);
	}

	return tile;
}