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

RectF RectF::fromCenter(const Vec2 & center, const float halfWidth, const float halfHeight)
{
	return RectF(Vec2(center.x - halfWidth, center.y - halfHeight), 
				 Vec2(center.x + halfWidth, center.y + halfHeight));
}
