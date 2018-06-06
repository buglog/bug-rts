#include "Frame.h"

Frame::Frame(const Vec2 & in_topLeft, const Vec2 & in_bottomRight)
{
	topLeft = in_topLeft;
	bottomRight = in_bottomRight;
	width = bottomRight.x - topLeft.x;
	height = bottomRight.y - topLeft.y;
	rect = RectF(topLeft, bottomRight);
}

void Frame::Draw(Graphics & gfx)
{
	gfx.RectBorder(rect, c);
}

RectF Frame::GetRect()
{
	return rect;
}
