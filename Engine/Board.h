#pragma once
#include "Vec2.h"
#include "RectF.h"
#include "Graphics.h"
#include "Mouse.h"
#include "Keyboard.h"

class Board
{
public: // once you're done with the tile class, make it private. Encapsulate your shit dawg
	class Frame
	{
	public:
		Frame() = default;
		Frame(const Vec2& in_topLeft, const Vec2& in_bottomRight);
		void Draw(Graphics& gfx);
		RectF GetRect();
	private:
		Color c = Colors::Red;
		Vec2 topLeft;
		Vec2 bottomRight;
		float width;
		float height;
		RectF rect;
	};
private:
	class Tile
	{
	public:
		Tile() = default;
		void Init(const Vec2& in_topLeft);
		void Draw(Graphics& gfx, const RectF& clamp);
		Vec2 GetCenter();
		void ProcessMouse(const Mouse& mouse);
		bool IsInFrame(Frame& frame);
	private:
		void DrawRect(Graphics& gfx, const RectF& clamp);
		void DrawTile(Graphics& gfx, const RectF& clamp);
		bool MouseIsOver(const Mouse& mouse);
	private:
		RectF rect;
		Vec2 topLeft;
		// diamond color and others
		Color c_diamond;
		Color c_lit, c_dead;
		// rect color to show it if you need to.
		Color c_rect;
		// diamond corners:
		Vec2 top, bottom, left, right;
	};
public:
	Board(const Vec2& in_topLeft, const Vec2& in_bottomRight);
	void Draw(Graphics& gfx);
	void ProcessOffset(Keyboard& kbd);
	void ProcessTiles(const Mouse& mouse);
private:
	Frame frame;
	Vec2 offset;
	float speed = 10.0f;
	Vec2 topLeft;
	Vec2 bottomRight;
	static constexpr int dimX = 5;
	static constexpr int dimY = 5;
	// width and height refer to the diamond shape, not the rect. Rect is half the width, so right now it's A Square.
	static constexpr float tileWidth = 100;
	static constexpr float tileHeight = 50;
	Tile tiles[dimX * dimY];
};
