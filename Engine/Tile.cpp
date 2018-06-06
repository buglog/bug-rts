#include "Tile.h"

void Tile::Init(const Vec2 & in_topLeft, const Location& in_loc)
{
	// tiles are drawn from top left corner of rect.
	loc = in_loc;
	topLeft = in_topLeft;
	// corners of diamond are then drawn from the center of the rect.
	rect = RectF(Vec2(topLeft.x, topLeft.y), Vec2(topLeft.x + width / 2.0f, topLeft.y + height));
	left = Vec2(GetCenter().x - width / 2.0f, GetCenter().y);
	right = Vec2(GetCenter().x + width / 2.0f, GetCenter().y);
	top = Vec2(GetCenter().x, GetCenter().y - height / 2.0f);
	bottom = Vec2(GetCenter().x, GetCenter().y + height / 2.0f);
	// sprite offset.
	// This sets up the spritePos as 
	spriteOffset.x -= width / 4;
	spriteOffset.y += height;
	spritePos = topLeft + spriteOffset;
	// colors
	c_rect.SetR(40);
	c_rect.SetG(40);
	c_rect.SetB(40);
	c_lit.SetR(170);
	c_lit.SetG(211);
	c_lit.SetB(98);
	c_dead.SetR(100);
	c_dead.SetG(0);
	c_dead.SetB(0);
}

void Tile::UpdateOffset(const Vec2 & in_topLeft)
{
	topLeft = in_topLeft;
	rect = RectF(Vec2(topLeft.x, topLeft.y), Vec2(topLeft.x + width / 2.0f, topLeft.y + height));
	left = Vec2(GetCenter().x - width / 2.0f, GetCenter().y);
	right = Vec2(GetCenter().x + width / 2.0f, GetCenter().y);
	top = Vec2(GetCenter().x, GetCenter().y - height / 2.0f);
	bottom = Vec2(GetCenter().x, GetCenter().y + height / 2.0f);
	spritePos = topLeft + spriteOffset;
}

void Tile::Draw(Graphics & gfx, const RectF& clamp)
{
	// DrawRect(gfx,clamp);
	DrawDiamond(gfx, clamp);
	gfx.PutPixelClamp(spritePos, Colors::Yellow, clamp);
}

Vec2 Tile::GetCenter()
{
	return RectF::GetCenter(rect);
}

Tile::Location Tile::GetLoc()
{
	return loc;
}

void Tile::DrawRect(Graphics & gfx, const RectF& clamp)
{
	gfx.RectBorderClamp(rect, c_rect, clamp);
}

void Tile::DrawDiamond(Graphics & gfx, const RectF& clamp)
{
	gfx.PutPixelClamp(left, c_diamond, clamp);
	gfx.PutPixelClamp(right, c_diamond, clamp);
	gfx.PutPixelClamp(top, c_diamond, clamp);
	gfx.PutPixelClamp(bottom, c_diamond, clamp);
	gfx.LineClamp(left, top, c_diamond, clamp);
	gfx.LineClamp(top, right, c_diamond, clamp);
	gfx.LineClamp(bottom, right, c_diamond, clamp);
	gfx.LineClamp(left, bottom, c_diamond, clamp);
}

void Tile::ProcessMouse(const Mouse & mouse)
{
	if (mouse.GetPosX() >= rect.left &&
		mouse.GetPosX() < rect.right &&
		mouse.GetPosY() >= rect.top &&
		mouse.GetPosY() < rect.bottom)
	{
		mouseIsOver = true;
		c_diamond = c_lit;
	}
	else
	{
		mouseIsOver = false;
		c_diamond = c_dead;
	}
}
