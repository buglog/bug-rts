#include "RectF.h"

RectF::RectF(const Vec2 & setTopLeft, const Vec2 & setBottomRight)
	:
	left(setTopLeft.x),
	right(setBottomRight.x),
	top(setTopLeft.y),
	bottom(setBottomRight.y),
	topLeft(setTopLeft),
	bottomRight(setBottomRight)
{
	width = right - left;
	height = bottom - top;
}

RectF::RectF(const Vec2 & setTopLeft, const float setWidth, const float setHeight)
	:
	topLeft(setTopLeft),
	width(setWidth),
	height(setHeight)
{
	left = topLeft.x;
	right = left + width;
	top = topLeft.y;
	bottom = top + height;
}

RectF::RectF(const float & in_left, const float & in_right, const float & in_top, const float & in_bottom)
	:
	left(in_left),
	right(in_right),
	top(in_top),
	bottom(in_bottom)
{
	width = right - left;
	height = bottom - top;
}

RectF RectF::FromCenter(const Vec2 & center, const float halfWidth, const float halfHeight)
{
	return RectF(Vec2(center.x - halfWidth, center.y - halfHeight), 
				 Vec2(center.x + halfWidth, center.y + halfHeight));
}

Vec2 RectF::GetCenter(const RectF& rect)
{
	return Vec2(rect.left + (rect.width / 2.0f), rect.top + (rect.height / 2.0f));
}

bool RectF::Contains(const Vec2 & pos) const
{
	return (pos.x >= left && pos.x <= right && pos.y >= top && pos.y <= bottom);
}

bool RectF::Overlaps(const RectF & rect) const
{
	return (right >= rect.left && left <= rect.right && bottom >= rect.top && top <= rect.bottom);
}
