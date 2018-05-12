#include "Board.h"

Board::Board(int in_dimX, int in_dimY)
	:
	dimX(in_dimX),
	dimY(in_dimY)
{
}

Board::Tile::Tile(const Vec2 & in_topLeft)
{
	topLeft = in_topLeft;
	rect = RectF(Vec2(topLeft.x, topLeft.y), Vec2(topLeft.x + tileWidth / 2.0f, topLeft.y + tileHeight));
	left   = Vec2( GetCenter().x - tileWidth / 2.0f, GetCenter().y );
	right  = Vec2( GetCenter().x + tileWidth / 2.0f, GetCenter().y );
	top    = Vec2( GetCenter().x, GetCenter().y - tileHeight / 2.0f );
	bottom = Vec2( GetCenter().x, GetCenter().y + tileHeight / 2.0f );
	// colors
	c_rect.SetR(40);
	c_rect.SetG(40);
	c_rect.SetB(40);
	c_diamond.SetR(211);
	c_diamond.SetR(211);
	c_diamond.SetR(211);
}

void Board::Tile::Draw(Graphics & gfx)
{
	DrawRect(gfx);
	DrawTile(gfx);
}

Vec2 Board::Tile::GetCenter()
{
	return RectF::GetCenter(rect);
}

void Board::Tile::ProcessMouse(const Mouse & mouse)
{
	if (MouseIsOver(mouse))
	{
		c_diamond = Colors::Green;
	}
	else
	{
		c_diamond = Colors::Gray;
	}
}

void Board::Tile::DrawRect(Graphics & gfx)
{
	gfx.RectBorder(rect, c_rect);
}

void Board::Tile::DrawTile(Graphics & gfx)
{
	gfx.PutPixel(left,  c_diamond);
	gfx.PutPixel(right, c_diamond);
	gfx.PutPixel(top,   c_diamond);
	gfx.PutPixel(bottom,c_diamond);
	gfx.Line(left, top    , c_diamond);
	gfx.Line(top, right   , c_diamond);
	gfx.Line(bottom, right, c_diamond);
	gfx.Line(left, bottom , c_diamond);
}

bool Board::Tile::MouseIsOver(const Mouse & mouse)
{
	if (mouse.GetPosX() >= rect.left &&
		mouse.GetPosX() <= rect.right &&
		mouse.GetPosY() >= rect.top &&
		mouse.GetPosY() <= rect.bottom)
	{
		return true;
	}
	return false;
}
