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
}

void Board::Tile::Draw(Graphics & gfx)
{
	// DrawRect(gfx);
	DrawTile(gfx);
}

Vec2 Board::Tile::GetCenter()
{
	return RectF::GetCenter(rect);
}

void Board::Tile::DrawRect(Graphics & gfx)
{
	gfx.RectBorder(rect, Colors::Blue);
}

void Board::Tile::DrawTile(Graphics & gfx)
{
	gfx.PutPixel(left,  c_tile);
	gfx.PutPixel(right, c_tile);
	gfx.PutPixel(top,   c_tile);
	gfx.PutPixel(bottom,c_tile);
	gfx.Line(left, top    , c_tile);
	gfx.Line(top, right   , c_tile);
	gfx.Line(bottom, right, c_tile);
	gfx.Line(left, bottom , c_tile);
}
