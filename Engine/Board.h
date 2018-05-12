#pragma once
#include "Vec2.h"
#include "RectF.h"
#include "Graphics.h"
#include "Mouse.h"

class Board
{
public: // once you're done with the tile class, make it private. Encapsulate your shit dawg
	class Tile
	{
	public:
		Tile() = default;
		void Init(const Vec2& in_topLeft);
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
		// colors to tell if the tile is selected
		Color c_lit;
		Color c_dead;
		// color of rect to show it if you need to
		Color c_rect;
		// diamond corners
		Vec2 top;
		Vec2 bottom;
		Vec2 left;
		Vec2 right;
	};
public:
	Board(const Vec2& in_topLeft);
	void Draw(Graphics& gfx);
	void ProcessTiles(const Mouse& mouse);
public:
	Vec2 topLeft;
	static constexpr int dimX = 5;
	static constexpr int dimY = 5;
	// width and height refer to the diamond shape, not the rect. Rect is half the width, so right now it's A Square.
	static constexpr float tileWidth = 100;
	static constexpr float tileHeight = 50;
	Tile tiles[dimX * dimY];
};
