#pragma once
#include "Vec2.h"
#include "RectF.h"
#include "Graphics.h"
#include "Mouse.h"
#include "Keyboard.h"

class Board
{
public:
	struct Location
	{
		Location() = default;
		Location(int in_x, int in_y)
		{
			Init(in_x, in_y);
		}
		void Init(int in_x, int in_y)
		{
			x = in_x;
			y = in_y;
		}
		Location operator+(const Location& rhs) const
		{
			return Location(x + rhs.x, y + rhs.y);
		}
		int x;
		int y;
	};

	class Frame
	{
	public:
		Frame() = default;
		Frame(const Vec2& in_topLeft, const Vec2& in_bottomRight);
		void Draw(Graphics& gfx);
		RectF GetRect();
	private:
		Color c = Colors::LightGray;
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
		void Init(const Vec2& in_topLeft,const Location& in_loc);
		void Update(const Vec2& in_topLeft);
		void Draw(Graphics& gfx, const RectF& clamp);
		void ProcessMouse(const Mouse& mouse);
		bool IsInFrame(Frame& frame);
		Vec2 GetCenter();
		Location GetLoc();
	private:
		void DrawRect(Graphics& gfx, const RectF& clamp);
		void DrawTile(Graphics& gfx, const RectF& clamp);
		bool MouseIsOver(const Mouse& mouse);
	private:
		Location loc;
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
	static constexpr float tileWidth = 100.0f;
	static constexpr float tileHeight = 50.0f;
	Tile tiles[dimX * dimY];
};
