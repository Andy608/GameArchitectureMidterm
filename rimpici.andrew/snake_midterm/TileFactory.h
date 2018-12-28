#ifndef TILE_FACTORY_H_
#define TILE_FACTORY_H_

#include <Trackable.h>
#include <Color.h>

class SettingsFile;
class Tile;
class Sprite;

class TileFactory : public Trackable
{
public:
	TileFactory(std::string tileDataSrc);
	~TileFactory();

	Tile* createNewTileFromColor(Color color, int x, int y) const;

private:
	const std::string WALL_TILE_IMAGE = "wall_tile_image";
	const std::string FLOOR_TILE_IMAGE = "floor_tile_image";

	SettingsFile* mpTileSettings;

	Sprite* mWallTileSprite;
	Sprite* mFloorTileSprite;
};

#endif