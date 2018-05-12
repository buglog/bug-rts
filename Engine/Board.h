#pragma once
#include "Vec2.h"
#include "RectF.h"
#include "Graphics.h"
#include "Mouse.h"

class Board
{
public:
	Board(int in_dimX,int in_dimY);
public:
	Vec2 topLeft;
	int dimX;
	int dimY;
	// width and height refer to the diamond shape, not the rect. Rect is half the width, so right now it's A Square.
	static constexpr float tileWidth = 100;
	static constexpr float tileHeight = 50;
public: // once you're done with the tile class, make it private. Encapsulate your shit dawg
	class Tile
	{
	public:
		Tile(const Vec2& in_topLeft);
		void Draw(Graphics& gfx);
		Vec2 GetCenter();
		void ProcessMouse(const Mouse& mouse);
	private:
		void DrawRect(Graphics& gfx);
		void DrawTile(Graphics& gfx);
		bool MouseIsOver(const Mouse& mouse);
	public:
		Color c_diamond;
	private:
		RectF rect;
		Vec2 topLeft;
		Color c_rect;
		// diamond corners
		Vec2 top;
		Vec2 bottom;
		Vec2 left;
		Vec2 right;
	};
};
