#pragma once
#include "Vec2.h"
#include "RectF.h"
#include "Graphics.h"

class Board
{
public:
	Board(int in_dimX,int in_dimY);
public:
	Vec2 topLeft;
	int dimX;
	int dimY;
	// width and height refer to the diamond shape, not the rect.
	// rect would be half the width, so 20 x 30 right now.
	static constexpr float tileWidth = 100;
	static constexpr float tileHeight = 50;
public: // once you're done with the tile class, it should be made private. Encapsulate your shit dawg
	class Tile
	{
	public:
		Tile(const Vec2& in_topLeft);
		void Draw(Graphics& gfx);
		Vec2 GetCenter();
	private:
		void DrawRect(Graphics& gfx);
		void DrawTile(Graphics& gfx);
	private:
		RectF rect;
		Vec2 topLeft;
		Color c_tile = Colors::Green;
		// diamond corners
		Vec2 top;
		Vec2 bottom;
		Vec2 left;
		Vec2 right;
	};
};
