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
		enum class Type
		{// make types simpler-- one thing per tile maybe
			Dirt,
			Flower
		};
	public:
		Tile() = default;
		void Init(const Vec2& in_topLeft,const Location& in_loc);
		void UpdateOffset(const Vec2& in_topLeft);
		void Draw(Graphics& gfx, const RectF& clamp);
		void DrawDiamond(Graphics& gfx, const RectF& clamp);
		void DrawRect(Graphics& gfx, const RectF& clamp);
		bool IsInFrame(Frame& frame);
		void ProcessMouse(const Mouse& mouse);
		Vec2 GetCenter();
		Location GetLoc();
	public:
		bool mouseIsOver = false;
	private:
		// where is the loc?
		Location loc;
		RectF rect;
		Vec2 topLeft;
		Vec2 spritePos = Vec2( topLeft.x - (tileWidth/4),topLeft.y );
		Vec2 spriteOffset;
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
	void ProcessInput(const Keyboard& kbd, const Mouse& mouse);
	Tile& TileAt(Location& loc);
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
	Location mouseLoc;
	float speed = 10.0f;
	static constexpr int dimX = 30;
	static constexpr int dimY = 20;
	// width and height refer to the diamond shape, not the rect. Rect is half the width, so right now it's A Square.
	static constexpr float tileWidth = 100.0f;
	static constexpr float tileHeight = 50.0f;
	Tile tiles[dimX * dimY];
};
