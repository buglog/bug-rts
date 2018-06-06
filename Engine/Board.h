#pragma once
#include "Vec2.h"
#include "RectF.h"
#include "Tile.h"
#include "Frame.h"
#include "Graphics.h"
#include "Mouse.h"
#include "Keyboard.h"

class Board
{
public:
	

public:
	Board(const Vec2& in_topLeft, const Vec2& in_bottomRight);
	void Draw(Graphics& gfx);
	void ProcessInput(const Keyboard& kbd, const Mouse& mouse);
	Tile& TileAt(Tile::Location& loc);
	const Vec2& GetOffset() const
	{
		return offset;
	}
private:
	void ClampTileArray(const int buffer);
	RectF GetTileArrayRect();
public:
	Frame frame;
private:
	Vec2 offset;
	Vec2 topLeft;
	Vec2 bottomRight;
	Tile::Location mouseLoc;
	float speed = 10.0f;
	static constexpr int dimX = 30;
	static constexpr int dimY = 20;
	// width and height refer to the diamond shape, not the rect. Rect is half the width, so right now it's A Square.
	
	Tile tiles[dimX * dimY];
};
