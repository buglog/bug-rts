#pragma once
#include "Vec2.h"

class RectF
{
public:
	RectF() = default;
	RectF(const Vec2& setTopLeft, const Vec2& setBottomRight);
	RectF(const Vec2& setTopLeft, const float setWidth, const float setHeight);
	RectF(const float& left, const float& right, const float& top, const float& bottom);
	static RectF FromCenter(const Vec2& center, const float halfWidth, const float halfHeight);
	static Vec2 GetCenter(const RectF& rect);
	bool Contains(const Vec2& pos) const;
	bool Overlaps(const RectF& rect) const;
public:
	Vec2 topLeft;
	Vec2 bottomRight;
	float left;
	float right;
	float top;
	float bottom;
	float width;
	float height;
};
