#include "Board.h"

Board::Board(const Vec2& in_topLeft,const Vec2& in_bottomRight)
	:
	topLeft(in_topLeft),
	bottomRight(in_bottomRight),
	frame(topLeft,bottomRight)
{
	int i = 0;
	for (int y = 0; y < dimY; ++y)
	{
		for (int x = 0; x < dimX; ++x)
		{
			Vec2 pos = Vec2(topLeft.x + x * tileWidth / 2.0f, topLeft.y + y * tileHeight);
			// if column is uneven, offset.
			if ((x % 2) > 0)
				pos.y += tileHeight / 2.0f;

			tiles[i].Init( pos );
			++i;
		}
	}
}

void Board::Draw(Graphics & gfx)
{
	for (Tile& t : tiles)
	{
		t.Draw(gfx);
	}
}

void Board::ProcessTiles(const Mouse & mouse)
{
	for (Tile& t : tiles)
	{
		t.ProcessMouse(mouse);
	}
}

void Board::Tile::Init(const Vec2 & in_topLeft)
{
	// tiles are drawn from top left corner of rect.
	topLeft = in_topLeft;
	// corners of diamond are then drawn from the center of the rect.
	rect = RectF(Vec2(topLeft.x, topLeft.y), Vec2(topLeft.x + tileWidth / 2.0f, topLeft.y + tileHeight));
	left   = Vec2( GetCenter().x - tileWidth / 2.0f, GetCenter().y );
	right  = Vec2( GetCenter().x + tileWidth / 2.0f, GetCenter().y );
	top    = Vec2( GetCenter().x, GetCenter().y - tileHeight / 2.0f );
	bottom = Vec2( GetCenter().x, GetCenter().y + tileHeight / 2.0f );
	// colors
	c_rect.SetR(40);
	c_rect.SetG(40);
	c_rect.SetB(40);
	c_lit.SetR(170);
	c_lit.SetG(211);
	c_lit.SetB(98);
	c_dead.SetR(70);
	c_dead.SetG(70);
	c_dead.SetB(30);
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
		c_diamond = c_lit;
	}
	else
	{
		c_diamond = c_dead; 
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

Board::Frame::Frame(const Vec2 & in_topLeft, const Vec2 & in_bottomRight)
	:
	topLeft(in_topLeft),
	bottomRight(in_bottomRight)
{
	width = bottomRight.x - topLeft.x;
	height = bottomRight.y - topLeft.y;
}
