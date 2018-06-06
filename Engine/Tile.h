#pragma once
#include "Vec2.h"
#include "RectF.h"
#include "Graphics.h"
#include "Mouse.h"

class Tile
{
public:
	struct Location
	{
	public:
		Location() = default;
		Location(int in_x, int in_y)
			:
			x(in_x),
			y(in_y)
		{
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
public:
	enum class Type
	{// make types simpler-- one thing per tile maybe
		Dirt,
		Flower
	};
public:
	Tile() = default;
	void Init(const Vec2& in_topLeft, const Location& in_loc);
	void UpdateOffset(const Vec2& in_topLeft);
	void Draw(Graphics& gfx, const RectF& clamp);
	void DrawDiamond(Graphics& gfx, const RectF& clamp);
	void DrawRect(Graphics& gfx, const RectF& clamp);
	
	void ProcessMouse(const Mouse& mouse);
	Vec2 GetCenter();
	Location GetLoc();
public:
	bool mouseIsOver = false;
public:
	static constexpr float width = 100.0f;
	static constexpr float height = 50.0f;
private:
	// where is the loc?
	Location loc;
	RectF rect;
	Vec2 topLeft;
	Vec2 spritePos = Vec2(topLeft.x - (width / 4), topLeft.y);
	Vec2 spriteOffset;
	// diamond color and others
	Color c_diamond;
	Color c_lit, c_dead;
	// rect color to show it if you need to.
	Color c_rect;
	// diamond corners:
	Vec2 top, bottom, left, right;
};