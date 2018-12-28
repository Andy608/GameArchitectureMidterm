#ifndef TILE_H_
#define TILE_H_

#include <Trackable.h>
#include <Vector2D.h>

class Sprite;

class Tile : public Trackable
{
public:
	Tile(Sprite* pSprite, int xPosition, int yPosition, bool isWall = false);
	virtual ~Tile();

	void update( float deltaTime );
	void draw();

	void setPosition(int xPosition, int yPosition);
	inline const Vector2D& getPosition() const { return mPosition; };
	inline const bool& isWall() const { return mIsWall; };

protected:
	Sprite* mpDefaultSprite;
	bool mIsWall;
	Vector2D mPosition;

	//Disable any form of copying for a Tile object.
	Tile(const Tile& copy) = delete;
	void operator=(const Tile& copy) = delete;
};

#endif