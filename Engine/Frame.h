#pragma once
#include "Vec2.h"
#include "RectF.h"
#include "Graphics.h"

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